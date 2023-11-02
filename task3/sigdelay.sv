module sigdelay #(
    parameter A_WIDTH=9,
                D_WIDTH = 8
)(
    //interface signals
    input logic         clk, //clock
    input logic         rst, //reset
    input logic         en, //enable
    input logic         wr,//write enable
    input logic         rd, //read enable
    input logic  [D_WIDTH-1:0] offset, //offset
    input logic [D_WIDTH-1:0] mic_signal, //microphone picks up
    output logic [D_WIDTH-1:0] delayed_signal //display mic signal but delayed    
);
    logic [A_WIDTH-1:0]  address; //interconnect wire

counter #(9) addrCounter (
    .clk (clk),
    .rst (rst),
    .en (en),
    .count (address)
);

ram #(9,8) signalRAM(
    .clk (clk),
    .wr_en (wr),
    .rd_en (rd),
    .wr_addr (address),
    .rd_addr (address-offset),
    .din (mic_signal),
    .dout (delayed_signal)
);

endmodule
