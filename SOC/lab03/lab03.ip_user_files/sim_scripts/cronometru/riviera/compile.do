vlib work
vlib riviera

vlib riviera/xil_defaultlib

vmap xil_defaultlib riviera/xil_defaultlib

vlog -work xil_defaultlib  -v2k5 \
"../../../bd/cronometru/ip/cronometru_numarator_59_0_0_0/sim/cronometru_numarator_59_0_0_0.v" \
"../../../bd/cronometru/sim/cronometru.v" \


vlog -work xil_defaultlib \
"glbl.v"

