`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// gngineer: 
// 
// Create Date: 05/20/2024 11:29:11 PM
// Design Name: 
// Module Name: sumator
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sumator(
    input [15:0] A,
    input [15:0] B,
    input Cin,
    output[15:0] S
    );
    
    // intrari
    wire gin[15:0];
    wire pin[15:0];
    wire pcarry = 0;
    
    intrare i0(A[0],   B[0],  gin[0],  pin[0]);
    intrare i1(A[1],   B[1],  gin[1],  pin[1]);
    intrare i2(A[2],   B[2],  gin[2],  pin[2]);
    intrare i3(A[3],   B[3],  gin[3],  pin[3]);
    intrare i4(A[4],   B[4],  gin[4],  pin[4]);
    intrare i5(A[5],   B[5],  gin[5],  pin[5]);
    intrare i6(A[6],   B[6],  gin[6],  pin[6]);
    intrare i7(A[7],   B[7],  gin[7],  pin[7]);
    intrare i8(A[8],   B[8],  gin[8],  pin[8]);
    intrare i9(A[9],   B[9],  gin[9],  pin[9]);
    intrare i10(A[10], B[10], gin[10], pin[10]);
    intrare i11(A[11], B[11], gin[11], pin[11]);
    intrare i12(A[12], B[12], gin[12], pin[12]);
    intrare i13(A[13], B[13], gin[13], pin[13]);
    intrare i14(A[14], B[14], gin[14], pin[14]);
    intrare i15(A[15], B[15], gin[15], pin[15]);
    
    // etajul 1 DE LA STANGA LA DREAPTA IN ORDINE
    wire gmid1[15:0];
    wire pmid1[15:0];
    mijloc mm1( gin[0],   pin[0],  Cin,     Pcarry,  gmid1[0],  pmid1[0]);
    mijloc m1( gin[2],   pin[2],  gin[1],  pin[1],  gmid1[2],  pmid1[2]);
    mijloc m3( gin[4],   pin[4],  gin[3],  pin[3],  gmid1[4],  pmid1[4]);
    mijloc m5( gin[6],   pin[6],  gin[5],  pin[5],  gmid1[6],  pmid1[6]);
    mijloc m7( gin[8],   pin[8],  gin[7],  pin[7],  gmid1[8],  pmid1[8]);
    mijloc m9(gin[10],  pin[10], gin[9],  pin[9],  gmid1[10], pmid1[10]);
    mijloc m11(gin[12],  pin[12], gin[11], pin[11], gmid1[12], pmid1[12]);
    mijloc m13(gin[14],  pin[14], gin[13], pin[13], gmid1[14], pmid1[14]);
    
    //etajul 2
    
    wire gmid2[15:0];
    wire pmid2[15:0];
    mijloc e2m11( gin  [1],   pin  [1],  gmid1[0],  pmid1[0],  gmid2[1],  pmid2[1]);
    mijloc e2m21( gmid1[2],   pmid1[2],  gmid1[0],  pmid1[0],  gmid2[2],  pmid2[2]);
    mijloc e2m53( gin  [5],   pin  [5],  gmid1[4],  pmid1[4],  gmid2[5],  pmid2[5]);
    mijloc e2m63( gmid1[6],   pmid1[6],  gmid1[4],  pmid1[4],  gmid2[6],  pmid2[6]);
    mijloc e2m97( gin  [9],   pin  [9],  gmid1[8],  pmid1[8],  gmid2[9],  pmid2[9]);
    mijloc e2m107(gmid1[10],  pmid1[10], gmid1[8],  pmid1[8],  gmid2[10], pmid2[10]);
    mijloc e2m1311(gin  [13],  pin  [13], gmid1[12], pmid1[12], gmid2[13], pmid2[13]);
    mijloc e2m1411(gmid1[14],  pmid1[14], gmid1[12], pmid1[12], gmid2[14], pmid2[14]);
    
    // etajul 3
    
    wire gmid3[15:0];
    wire pmid3[15:0];
    mijloc e3m31( gin  [3],   pin  [3],  gmid2[2],  pmid2[2],  gmid3[3],  pmid3[3]);
    mijloc e3m41( gmid1[4],   pmid1[4],  gmid2[2],  pmid2[2],  gmid3[4],  pmid3[4]);
    mijloc e3m51( gmid2[5],   pmid2[5],  gmid2[2],  pmid2[2],  gmid3[5],  pmid3[5]);
    mijloc e3m61( gmid2[6],   pmid2[6],  gmid2[2],  pmid2[2],  gmid3[6],  pmid3[6]);
    mijloc e3m117(gin  [11],  pin  [11], gmid2[10], pmid2[10], gmid3[11], pmid3[11]);
    mijloc e3m127(gmid1[12],  pmid1[12], gmid2[10], pmid2[10], gmid3[12], pmid3[12]);
    mijloc e3m137(gmid2[13],  pmid2[13], gmid2[10], pmid2[10], gmid3[13], pmid3[13]);
    mijloc e3m147(gmid2[14],  pmid2[14], gmid2[10], pmid2[10], gmid3[14], pmid3[14]);
    
    // etajul 4
    
    wire gmid4[15:0];
    wire pmid4[15:0];
    mijloc e4m7( gin  [7],   pin  [7],  gmid3[6],  pmid3[6], gmid4[7],  pmid4[7]);
    mijloc e4m8( gmid1[8],   pmid1[8],  gmid3[6],  pmid3[6], gmid4[8],  pmid4[8]);
    mijloc e4m9( gmid2[9],   pmid2[9],  gmid3[6],  pmid3[6], gmid4[9],  pmid4[9]);
    mijloc e4m10(gmid2[10],  pmid2[10], gmid3[6],  pmid3[6], gmid4[10], pmid4[10]);
    mijloc e4m11(gmid3[11],  pmid3[11], gmid3[6],  pmid3[6], gmid4[11], pmid4[11]);
    mijloc e4m12(gmid3[12],  pmid3[12], gmid3[6],  pmid3[6], gmid4[12], pmid4[12]);
    mijloc e4m13(gmid3[13],  pmid3[13], gmid3[6],  pmid3[6], gmid4[13], pmid4[13]);
    mijloc e4m14(gmid3[14],  pmid3[14], gmid3[6],  pmid3[6], gmid4[14], pmid4[14]);
    
    // Iesire.
    
    iesire o0( A[0],  B[0],  Cin,       S[0]);
    iesire o1( A[1],  B[1],  gmid1[0],  S[1]);
    iesire o2( A[2],  B[2],  gmid2[1],  S[2]);
    iesire o3( A[3],  B[3],  gmid2[2],  S[3]);
    iesire o4( A[4],  B[4],  gmid3[3],  S[4]);
    iesire o5( A[5],  B[5],  gmid3[4],  S[5]);
    iesire o6( A[6],  B[6],  gmid3[5],  S[6]);
    iesire o7( A[7],  B[7],  gmid3[6],  S[7]);
    iesire o8( A[8],  B[8],  gmid4[7],  S[8]);
    iesire o9( A[9],  B[9],  gmid4[8],  S[9]);
    iesire o10(A[10], B[10], gmid4[9],  S[10]);
    iesire o11(A[11], B[11], gmid4[10], S[11]);
    iesire o12(A[12], B[12], gmid4[11], S[12]);
    iesire o13(A[13], B[13], gmid4[12], S[13]);
    iesire o14(A[14], B[14], gmid4[13], S[14]);
    iesire o15(A[15], B[15], gmid4[14], S[15]);
endmodule
