vlib questa_lib/work
vlib questa_lib/msim

vlib questa_lib/msim/xil_defaultlib

vmap xil_defaultlib questa_lib/msim/xil_defaultlib

vlog -work xil_defaultlib  -incr -mfcu \
"../../../bd/cronometru/ip/cronometru_numarator_59_0_0_0/sim/cronometru_numarator_59_0_0_0.v" \
"../../../bd/cronometru/sim/cronometru.v" \


vlog -work xil_defaultlib \
"glbl.v"

