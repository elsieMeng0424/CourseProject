`timescale 1ns / 1ps
module score(
	input clock,
	input reset,
	input get_apple,
	input get_apple2,
	input get_apple3,
	input get_apple4,
	input get_apple5,
	input [1:0] game_status,
	
	output [7:0] an,
	output [7:0] seg
    );
    
    localparam LAUNCHING=2'b00;
    localparam PLAYING=2'b01;
    localparam DIE_FLASHING=2'b10;
    localparam INITIALIZING=2'b11;
    
    wire real_enable;
    wire real_reset;
    
    reg [31:0]Myscore;
    
    always @(posedge clock)
    begin
         if((reset==1) | ((game_status==INITIALIZING) == 1))
            Myscore = 0; 
         else if((get_apple==1) && (game_status==PLAYING) == 1)
            Myscore = Myscore + 1; 
         else if((get_apple2==1) && (game_status==PLAYING)==1)
            Myscore = Myscore + 1;
         else if((get_apple3==1) && (game_status==PLAYING)==1)
            Myscore = Myscore + 3; 
         else if((get_apple4==1) && (game_status==PLAYING) == 1)
            Myscore = Myscore + 1; 
         else if((get_apple5==1) && (game_status==PLAYING)==1)
            Myscore = Myscore + 1;                 
    end
    
    reg [31:0]total_time;
    reg [127:0]total_time_10ns;
    always @(posedge clock)
    begin
        
        if(game_status == PLAYING)
        begin
            total_time_10ns <= total_time_10ns + 1;  
            if(total_time_10ns % 100000000 == 1) 
                total_time <= total_time + 1; 
        end
        else if(game_status == INITIALIZING)
        begin
            total_time_10ns <= 0;
            total_time <= 0;
        end
    end

    seg (
        .reset(reset),
        .clock(clock),
        .an(an),
        .seg(seg),
    	.score(Myscore),
    	.total_time(total_time)
        ); 
endmodule
