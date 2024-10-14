vlib work
vlib activehdl

vlib activehdl/xil_defaultlib

vmap xil_defaultlib activehdl/xil_defaultlib

vlog -work xil_defaultlib  -v2k5 \
"../../../bd/cronometru/ip/cronometru_numarator_59_0_0_0/sim/cronometru_numarator_59_0_0_0.v" \
"../../../bd/cronometru/sim/cronometru.v" \


vlog -work xil_defaultlib \
"glbl.v"

