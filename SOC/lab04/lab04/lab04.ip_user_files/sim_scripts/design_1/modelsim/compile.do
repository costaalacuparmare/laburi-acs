vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work xil_defaultlib  -incr -mfcu \
"../../../bd/design_1/ip/design_1_sumator4b_0_0/sim/design_1_sumator4b_0_0.v" \
"../../../bd/design_1/ip/design_1_sumator4b_1_0/sim/design_1_sumator4b_1_0.v" \
"../../../bd/design_1/ip/design_1_sumator4b_2_0/sim/design_1_sumator4b_2_0.v" \
"../../../bd/design_1/ip/design_1_sumator4b_3_0/sim/design_1_sumator4b_3_0.v" \
"../../../bd/design_1/ip/design_1_uat_0_0/sim/design_1_uat_0_0.v" \
"../../../bd/design_1/ip/design_1_intrare_0_0/sim/design_1_intrare_0_0.v" \
"../../../bd/design_1/ip/design_1_iesire_0_0/sim/design_1_iesire_0_0.v" \
"../../../bd/design_1/sim/design_1.v" \


vlog -work xil_defaultlib \
"glbl.v"

