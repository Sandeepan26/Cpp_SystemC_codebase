#include "systemc"
using namespace sc_dt;
using namespace sc_core;

SC_MODULE(RAM){
	sc_in<bool> clk, rw;
  	sc_port<sc_signal_in_if<sc_bv<32>>> address_request, data_request;
  	sc_port<sc_signal_out_if<sc_bv<32>>> data_response;
  
  
  sc_lv<32> memory [2147483648];  //4Mx32 memory
  
  void read_write(){
    if(rw.read())
      memory[address_request->read().to_int()] = data_request->read();
    else
      data_response->write(memory[address_request->read().to_int()]);
  
  }
  
  SC_CTOR(RAM){
  SC_METHOD(read_write);
  sensitive << clk.pos();
  dont_initialize();
  }
  
};
