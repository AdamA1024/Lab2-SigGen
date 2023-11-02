#!/bin/sh

#cleanup

rm -rf obj_dir
rm -f sigdelay.vcd

# run verilator to translate verilog -> C++
verilator -Wall --cc --trace sigdelay.sv --exe sigdelay_tb.cpp

#build C++ project via make automatically generated by verilator
make -j -C obj_dir/ -f Vsigdelay.mk Vsigdelay

#run executable simulation file
obj_dir/Vsigdelay