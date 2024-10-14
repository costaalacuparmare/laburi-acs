`timescale 1ns / 1ps

module vending_machine (
    input wire clk,
    input wire reset,
    input wire [7:0] inputs,
    output reg product1_selected,
    output reg product2_selected,
    output reg product3_selected,
    output reg change_50bani,
    output reg change_1leu,
    output reg insufficient_funds,
    output reg cash_overflow
);

    // State declarations using localparam
    localparam PARSE_INPUT = 1'b0;
    localparam CHANGE = 1'b1;

    reg state, nextstate;

    // Registers for shared variables
    reg [7:0] credit = 8'd0;
    reg [7:0] nr_bills = 8'd0;
    reg [7:0] nr_coins = 8'd0;
    reg bought_product = 1'b0;

    // State register
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= PARSE_INPUT;
        end else begin
            state <= nextstate;
        end
  //  end

    // Next state logic and output logic
   // always @(*) begin
        product1_selected <= 1'b0;
        product2_selected <= 1'b0;
        product3_selected <= 1'b0;
        change_50bani <= 1'b0;
        change_1leu <= 1'b0;
        insufficient_funds <= 1'b0;
        cash_overflow <= 1'b0;

        case (state)
            PARSE_INPUT: begin
                if (credit <= 8'd150) begin
                    case (inputs)
                        8'b10000000: begin
                            credit <= credit + 8'd5;
                            nr_coins <= nr_coins + 8'd1;
                        end
                        8'b01000000: begin
                            credit <= credit + 8'd10;
                            nr_bills <= nr_bills + 8'd1;
                        end
                        8'b00100000: begin
                            credit <= credit + 8'd50;
                        end
                        8'b00010000: begin
                            credit <= credit + 8'd100;
                        end
                    endcase
                end else begin
                    cash_overflow <= 1'b1;
                    credit <= 8'd150;
                end

                if (inputs == 8'b00001000) begin
                    if (credit >= 8'd25) begin
                        bought_product <= 1'b1;
                        credit <= credit - 8'd25;
                        product1_selected <= 1'b1;
                    end else begin
                        insufficient_funds <= 1'b1;
                    end
                end

                if (inputs == 8'b00000100) begin
                    if (credit >= 8'd30) begin
                        bought_product <= 1'b1;
                        credit <= credit - 8'd30;
                        product2_selected <= 1'b1;
                    end else begin
                        insufficient_funds <= 1'b1;
                    end
                end

                if (inputs == 8'b00000010) begin
                    if (credit >= 8'd50) begin
                        bought_product <= 1'b1;
                        credit <= credit - 8'd50;
                        product3_selected <= 1'b1;
                    end else begin
                        insufficient_funds <= 1'b1;
                    end
                end

                if (inputs == 8'b00000001) begin
                    nextstate <= CHANGE;
                end else begin
                    nextstate <= PARSE_INPUT;
                end
            end

            CHANGE: begin
                if (credit != 8'd0) begin
                    if (!bought_product) begin
                        credit <= credit - 8'd10;
                    end

                    if (credit >= 8'd10 && nr_bills != 8'd0) begin
                        nr_bills <= nr_bills - 8'd1;
                        credit <= credit - 8'd10;
                        change_1leu <= 1'b1;
                        nextstate <= CHANGE;
                    end else if (nr_coins != 8'd0) begin
                        nr_coins <= nr_coins - 8'd1;
                        credit <= credit - 8'd5;
                        change_50bani <= 1'b1;
                        nextstate <= CHANGE;
                    end else begin
                        insufficient_funds <= 1'b1;
                        nextstate <= PARSE_INPUT;
                        bought_product <= 1'b0;
                    end
                end else begin
                    nextstate <= PARSE_INPUT;
                    bought_product <= 1'b0;
                end
            end

            default: begin
                nextstate <= PARSE_INPUT;
                bought_product <= 1'b0;
            end
        endcase
    end

endmodule
