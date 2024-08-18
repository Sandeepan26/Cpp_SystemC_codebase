#include "systemc"
#include "direct_mapped_cache.cpp"
#include<iostream>

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(Cache_top){
  
  sc_clock clock_signal_cache;
  sc_in<bool> cpu_rw;
  
  sc_port<sc_signal_in_if<sc_bv<32>>> cpu_data_req, cpu_address_req, mem_to_cache_data;
  sc_port<sc_signal_out_if<sc_bv<32>>> cache_data_out;
  sc_port<sc_signal_out_if<sc_bv<32>>> cache_to_mem_data, cache_to_mem_address;
  sc_port<sc_signal_out_if<bool>> cache_rw;
  
  Cache cache_inst;
  
  SC_CTOR(Cache_top):cache_inst("cache_inst"), clock_signal_cache("clock_signal_cache", 10, SC_NS, 0.5){
    
    //named port connection
    
  	cache_inst.clk(clock_signal_cache);
  	cache_inst.wr_en(cpu_rw);
  	cache_inst.cpu_request_address(cpu_address_req);
  	cache_inst.cpu_request_data(cpu_data_req);
  	cache_inst.mem_to_cache_data(mem_to_cache_data);
  	cache_inst.cache_data_out(cache_data_out);
  	cache_inst.cache_to_mem_data(cache_to_mem_data);
  	cache_inst.cache_to_mem_address(cache_to_mem_address);
  	cache_inst.wen(cache_rw);
 
  }

};


SC_MODULE(RAM_top){
  sc_in<bool> rw;
  sc_port<sc_signal_in_if<sc_bv<32>>> request_address, request_data;
  sc_port<sc_signal_out_if<sc_bv<32>>> response;
  
  sc_clock clock_signal_ram;
  
  RAM ram_inst;
  
  SC_CTOR(RAM_top) : ram_inst("ram_inst"), clock_signal_ram("clock_signal_ram", 10, SC_NS, 0.5){
  
 	//positional port connection  
  	ram_inst(clock_signal_ram, rw, request_address, request_data, response);
  }
  
};


SC_MODULE(TOP){
  
  sc_clock clock_signal;
  
 sc_signal<bool> cpu_rw, cache_rw;
 sc_signal<sc_bv<32>> cpu_address, cpu_data, mem_to_cache_data, cache_to_mem_data, cache_to_mem_address, cache_data_out;
  
  void write_data(){
    cpu_rw.write('1');
    cpu_address.write(1024);
    cpu_data.write(128);
  }
  
  void read_data(){
  	cpu_rw.write('0');
    cpu_address.write(1024);
    std::cout << "Data read from Cache"<<cache_data_out.read()<<std::endl;
   
  }
  
  SC_CTOR(TOP): clock_signal("clock_signal", 10, SC_NS){
  	Cache_top c_top("ctop");
    RAM_top r_top("rtop");
   	SC_THREAD(write_data);
    dont_initialize();
  	SC_METHOD(read_data);
    sensitive << cache_data_out;
    
    
    c_top.cpu_rw(cpu_rw);
    c_top.cpu_data_req(cpu_data);
    c_top.cpu_address_req(cpu_address);
    c_top.cache_data_out(cache_data_out);
    c_top.cache_to_mem_data(cache_to_mem_data);
    c_top.cache_to_mem_address(cache_to_mem_address);
    c_top.cache_rw(cache_rw);
    
    
    r_top.rw(cache_rw);
    r_top.request_address(cache_to_mem_address);
    r_top.request_data(cache_to_mem_data);
    r_top.response(mem_to_cache_data);
  }
};


int sc_main (int argc, char* argv[]){
 
	sc_start(1, SC_SEC);  
  
  return 0;
}
