#include "systemc"
#include "ram.cpp"
using namespace sc_core;
using namespace sc_dt;
  
//This is a Cache module with ports receiving signals at the boundary

SC_MODULE (Cache){
  sc_in<bool> clk, wr_en;
  sc_port<sc_signal_in_if<sc_bv<32>>> cpu_request_address, cpu_request_data, mem_to_cache_data;
  sc_port<sc_signal_out_if<sc_bv<32>>> cache_data_out, cache_to_mem_data, cache_to_mem_address;
  sc_port<sc_signal_out_if<bool>> wen;

  
  //cache_block cache_block_line[1024]; //1024 cache block lines
  
  sc_lv<53> cache_block_line[128][8]; //Cache block divided into eight sets with 128 cache block lines each
  
  enum cache_states {idle = 0, compare = 1, allocate = 2, write_through = 3};
    
    cache_states state = idle;
  
void assign_write_en(){
  while(true){
  	wen->write(wr_en->read() == '1');
  }
}

  void assign_address(){
    while(true){
    	cache_to_mem_address->write(cpu_request_address->read());	
    }
  }
  
  void check_state(){
    switch(state){
    case idle: state = compare;
      break;
     case compare: 
     while (true){
        	if(cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()].range(51,32) == cpu_request_address->read().range(31,12))
          		if(cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()][53] == SC_LOGIC_1)
           			cache_data_out->write(cache_block_line[cpu_request_address->read().range(31,12).to_int()][cpu_request_address->read().range(4,2).to_int()].range(31,0));
           		else
           			state = idle;
            else{
           		state = allocate;
              	cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()].range(51,32) =(cpu_request_address->read().range(31,12));
        }
     
     }
     
           break;
      case allocate:
      while(wr_en->read() == SC_LOGIC_1){
        cache_data_out->write(mem_to_cache_data->read());
        cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()].range(31,0)=(mem_to_cache_data->read());
        cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()][53] = SC_LOGIC_1; //set valid bit
        state = (cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()][53] == SC_LOGIC_1) ? compare : allocate;
      }
      break;
      case write_through:
      while(true){
      cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()].range(31,0) = cpu_request_data->read();
      cache_to_mem_data->write(cache_block_line[cpu_request_address->read().range(11,5).to_int()][cpu_request_address->read().range(4,2).to_int()].range(31,0));

      state = idle;
      }
      
    default : state = idle;
    } //switch
      
  }
  
  
SC_CTOR(Cache){
  SC_THREAD(assign_write_en);
  dont_initialize();
  SC_THREAD(assign_address);
  dont_initialize();
  SC_CTHREAD(check_state, clk.pos()); 
  dont_initialize();
}

};
