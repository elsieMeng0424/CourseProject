`timescale 1ns / 1ps

module fsm(
    input reset,
    input clock,
    input hit_wall,
    input hit_itself,
    input up,right,down,left,
    input kup,kright,kdown,kleft,
    input pause,
    output reg [1:0] game_status
    );
	localparam PAUSED=2'b00;       //暂停
    localparam PLAYING=2'b01;      //游戏中
    localparam DIE_FLASHING=2'b10; //死亡闪烁
    localparam INITIALIZING=2'b11; //初始化
    reg [27:0] count_two; // count_two用来做死亡闪烁的延时
    
	initial
	begin
	game_status<=INITIALIZING;
	count_two<=0;
	end
	
    always @(posedge clock)
    begin
    	if (reset==1) 
    	    game_status<=INITIALIZING;
        else if (pause == 1)
            game_status <= PAUSED;
		else if (game_status==PLAYING && (hit_wall==1 || hit_itself==1))
		begin
		game_status<=DIE_FLASHING;
		count_two<=0;
		end	
		else if (game_status==DIE_FLASHING)
		begin
			if (count_two==200000000) begin game_status<=INITIALIZING; count_two<=0; end
			else count_two <= count_two+1; // count_two用来做死亡闪烁的延时
		end
		else if ((game_status == INITIALIZING || game_status == PAUSED) && ( up==1 || right==1 || down==1 || left==1 || kup==1||kdown==1||kleft==1||kright==1))
		begin
		game_status <= PLAYING; // 按下任意按键时游戏开始
		end
    end
endmodule
