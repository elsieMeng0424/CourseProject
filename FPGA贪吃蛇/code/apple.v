`timescale 1ns / 1ps
module apple(
    input clock,
    input get_apple,
    input get_apple2,
    input get_apple3,
    input get_apple4,
    input get_apple5,
    input [1:0] game_status,
    
    output reg [5:0] apple_x,
    output reg [5:0] apple_y,
    output reg [5:0] apple2_x,
    output reg [5:0] apple2_y,
    output reg [5:0] apple3_x,
    output reg [5:0] apple3_y,
    output reg [5:0] apple4_x,
    output reg [5:0] apple4_y,
    output reg [5:0] apple5_x,
    output reg [5:0] apple5_y
    );
    
	localparam LAUNCHING=2'b00;
    localparam PLAYING=2'b01;
    localparam DIE_FLASHING=2'b10;
    localparam INITIALIZING=2'b11;
    
    // 用于随机（伪）生成苹果坐标
    reg [11:0] random_for_x;
    reg [11:0] random_for_y;

    initial 
    begin
		random_for_x<=521;
		random_for_y<=133;
    end
    
    always @(posedge clock)
    begin
    	random_for_x<=random_for_x+997;
    	random_for_y<=random_for_x+793;
    	
    	if (game_status==INITIALIZING)
			begin
			//苹果的初始位置，四个红苹果围一个金苹果
			apple_x<=20;
			apple_y<=9;
			apple2_x<=20;
			apple2_y<=17;
			apple3_x<=25;
			apple3_y<=13;
			apple4_x<=30;
            apple4_y<=9;
            apple5_x<=30;
            apple5_y<=17;
			random_for_x<=521;
			random_for_y<=133;
			end
    	else
    	if (game_status==PLAYING && get_apple==1)
		begin
			// 防止苹果x和y坐标超范围
			apple_x<=(random_for_x[5:0]+1>46?(random_for_x[5:0]+1-20):(random_for_x[5:0]+1));
			apple_y<=(random_for_y[4:0]+1>25?(random_for_y[4:0]+1-10):(random_for_y[4:0]+1));
		end
		else
		if(game_status==PLAYING && get_apple2==1)
		begin
		    apple2_x<=(random_for_x[5:0]+1>46?(random_for_x[5:0]+1-20):(random_for_x[5:0]+1));
		    apple2_y<=(random_for_y[4:0]+1>25?(random_for_y[4:0]+1-10):(random_for_y[4:0]+1));
		end
		else
		if(game_status==PLAYING && get_apple3==1)
		begin
		    apple3_x<=(random_for_x[5:0]+1>46?(random_for_x[5:0]+1-20):(random_for_x[5:0]+1));
		    apple3_y<=(random_for_y[4:0]+1>25?(random_for_y[4:0]+1-10):(random_for_y[4:0]+1));
		end
		else
        if(game_status==PLAYING && get_apple4==1)
        begin
            apple4_x<=(random_for_x[5:0]+1>46?(random_for_x[5:0]+1-20):(random_for_x[5:0]+1));
            apple4_y<=(random_for_y[4:0]+1>25?(random_for_y[4:0]+1-10):(random_for_y[4:0]+1));
        end
		else
        if(game_status==PLAYING && get_apple5==1)
        begin
            apple5_x<=(random_for_x[5:0]+1>46?(random_for_x[5:0]+1-20):(random_for_x[5:0]+1));
            apple5_y<=(random_for_y[4:0]+1>25?(random_for_y[4:0]+1-10):(random_for_y[4:0]+1));
        end
    	else 
    	begin
			apple_x<=apple_x;
			apple_y<=apple_y;
			apple2_x<=apple2_x;
			apple2_y<=apple2_y;
			apple3_x<=apple3_x;
			apple3_y<=apple3_y;
			apple4_x<=apple4_x;
            apple4_y<=apple4_y;
            apple5_x<=apple5_x;
            apple5_y<=apple5_y;
    	end
    end
endmodule
