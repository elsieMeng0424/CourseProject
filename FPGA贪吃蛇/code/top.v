`timescale 1ns / 1ps

module top(
    input CLK100MHZ, // 100MHz时钟
    input reset, // 复位信号
    input up,right,down,left, // 方向键，上下左右
    input [2:0] speed, // 速度(0为暂停)
    input [2:0] snake_color, //蛇的颜色(低位至高位分别为R、G、B) 
    input difficult, //难度
    input difficult2,
    
    output [7:0] an, // 数码管使能
    output [7:0] seg, // 数码管输出
    output [11:0] vga, // vga显示输出，顺序为R,G,B各4位
    output h_sync,v_sync, // 行、列扫描信号
    
    output AUD_PWM,     //音频输出波形
    output AUD_SD,       //音频输出控制
    
    input key_data,
    input key_clk
    );
    
    localparam PAUSED=2'b00;       //暂停
    localparam PLAYING=2'b01;      //游戏中
    localparam DIE_FLASHING=2'b10; //死亡闪烁
    localparam INITIALIZING=2'b11; //初始化
    
    wire is_pause;
    assign is_pause = (speed == 3'b0) ? 1'b1 : 1'b0;
    	
	// 用于模块间传递二维数组 [5:0] snake_x/y [31:0]
    wire [32*6-1:0] snake_x_temp; // 蛇身坐标临时变量
    wire [32*6-1:0] snake_y_temp; // 蛇身坐标临时变量
    
	wire [31:0] snake_piece_is_display;  // 控制体长
	
	wire [5:0] apple_x; // 苹果坐标
	wire [5:0] apple_y; // 苹果坐标
	wire [5:0] apple2_x;
	wire [5:0] apple2_y;
	wire [5:0] apple3_x;
	wire [5:0] apple3_y;
	wire [5:0] apple4_x;
	wire [5:0] apple4_y;
	wire [5:0] apple5_x;
	wire [5:0] apple5_y;
	
	wire [5:0] wall_x;
	wire [5:0] wall_y;
	assign wall_x = difficult?10:0;
	assign wall_y = difficult?5:0;
    wire [5:0] wall2_x;
    wire [5:0] wall2_y;
    assign wall2_x = difficult?10:0;
    assign wall2_y = difficult?21:0;
    wire [5:0] wall3_x;
    wire [5:0] wall3_y;
    assign wall3_x = difficult?40:0;
    assign wall3_y = difficult?5:0;
    wire [5:0] wall4_x;
    wire [5:0] wall4_y;
    assign wall4_x = difficult?40:0;
    assign wall4_y = difficult?21:0;
    
	wire [5:0] wall5_x;
    wire [5:0] wall5_y;
    assign wall5_x = (difficult & difficult2)?25:0;
    assign wall5_y = (difficult & difficult2)?9:0;
    wire [5:0] wall6_x;
    wire [5:0] wall6_y;
    assign wall6_x = (difficult & difficult2)?25:0;
    assign wall6_y = (difficult & difficult2)?17:0;
    wire [5:0] wall7_x;
    wire [5:0] wall7_y;
    assign wall7_x = (difficult & difficult2)?20:0;
    assign wall7_y = (difficult & difficult2)?13:0;
    wire [5:0] wall8_x;
    wire [5:0] wall8_y;
    assign wall8_x = (difficult & difficult2)?30:0;
    assign wall8_y = (difficult & difficult2)?13:0;
	
	// 游戏状态 00: PAUSED  01: PLAYING   10:DIE_FLASHING   11: INITIALIZING
	wire [1:0] game_status; 
	
	// 方向 00: UP   01: Right   10: DOWN   11: LEFT
	wire [1:0] current_direction;
	wire [1:0] next_direction;	
	
	wire get_apple; // 吃到苹果
	wire get_apple2;
	wire get_apple3;
	wire get_apple4;
	wire get_apple5;
	
	wire hit_wall; // 撞墙否
	wire hit_itself; // 撞己否	
	
	wire kup,kdown,kleft,kright;//键盘控制的方向键

    display (
        .clock(CLK100MHZ), // 在display内部做时钟转换
        .h_sync(h_sync),
        .v_sync(v_sync),
        .vga(vga),
        .game_status(game_status),
        .apple_x(apple_x),
        .apple_y(apple_y),
        .apple2_x(apple2_x),
        .apple2_y(apple2_y),
        .apple3_x(apple3_x),
        .apple3_y(apple3_y),
        .apple4_x(apple4_x),
        .apple4_y(apple4_y),
        .apple5_x(apple5_x),
        .apple5_y(apple5_y),
        .wall_x(wall_x),
        .wall_y(wall_y),
        .wall2_x(wall2_x),
        .wall2_y(wall2_y),
        .wall3_x(wall3_x),
        .wall3_y(wall3_y),
        .wall4_x(wall4_x),
        .wall4_y(wall4_y),
        .wall5_x(wall5_x),
        .wall5_y(wall5_y),
        .wall6_x(wall6_x),
        .wall6_y(wall6_y),
        .wall7_x(wall7_x),
        .wall7_y(wall7_y),
        .wall8_x(wall8_x),
        .wall8_y(wall8_y),
        .snake_x_temp(snake_x_temp),
        .snake_y_temp(snake_y_temp),
        .snake_piece_is_display(snake_piece_is_display),
        .snake_color(snake_color)
        );
    
    snake (
    	.clock(CLK100MHZ),
    	.speed(speed),
    	.snake_x_temp(snake_x_temp),
    	.snake_y_temp(snake_y_temp),
    	.apple_x(apple_x),
    	.apple_y(apple_y),
    	.apple2_x(apple2_x),
    	.apple2_y(apple2_y),
    	.apple3_x(apple3_x),
    	.apple3_y(apple3_y),
        .apple4_x(apple4_x),
        .apple4_y(apple4_y),
        .apple5_x(apple5_x),
        .apple5_y(apple5_y),
        .wall_x(wall_x),
        .wall_y(wall_y),
        .wall2_x(wall2_x),
        .wall2_y(wall2_y),
        .wall3_x(wall3_x),
        .wall3_y(wall3_y),
        .wall4_x(wall4_x),
        .wall4_y(wall4_y),
        .wall5_x(wall5_x),
        .wall5_y(wall5_y),
        .wall6_x(wall6_x),
        .wall6_y(wall6_y),
        .wall7_x(wall7_x),
        .wall7_y(wall7_y),
        .wall8_x(wall8_x),
        .wall8_y(wall8_y),        
    	.snake_piece_is_display(snake_piece_is_display),
    	.get_apple(get_apple),
    	.get_apple2(get_apple2),
    	.get_apple3(get_apple3),
    	.get_apple4(get_apple4),
    	.get_apple5(get_apple5),
    	.game_status(game_status),
        .current_direction(current_direction),
    	.next_direction(next_direction),
    	.hit_wall(hit_wall),
    	.hit_itself(hit_itself)
    	);
     
    fsm (
        .reset(reset),
        .clock(CLK100MHZ),
        .game_status(game_status),
        .hit_wall(hit_wall),
        .hit_itself(hit_itself),
    	.up(up),
        .right(right),
        .down(down),
        .left(left),
        .kup(kup),
        .kdown(kdown),
        .kleft(kleft),
        .kright(kright),
        .pause(is_pause)
        );
    
    get_direction Get_direction (
    	.clock(CLK100MHZ),
    	.up(up),
    	.right(right),
    	.down(down),
    	.left(left),
    	.kup(kup),
    	.kdown(kdown),
    	.kleft(kleft),
    	.kright(kright),
    	.current_direction(current_direction),
    	.next_direction(next_direction)
    	);
    	
    apple (
        .clock(CLK100MHZ),
        .apple_x(apple_x),
        .apple_y(apple_y),
        .apple2_x(apple2_x),
        .apple2_y(apple2_y),
        .apple3_x(apple3_x),
        .apple3_y(apple3_y),
        .apple4_x(apple4_x),
        .apple4_y(apple4_y),
        .apple5_x(apple5_x),
        .apple5_y(apple5_y),
        .get_apple(get_apple),
        .get_apple2(get_apple2),
        .get_apple3(get_apple3),
        .get_apple4(get_apple4),
        .get_apple5(get_apple5),
        .game_status(game_status)
        );
        
    score (
    	.reset(reset),
    	.clock(CLK100MHZ),
    	.get_apple(get_apple),
    	.get_apple2(get_apple2),
    	.get_apple3(get_apple3),
    	.get_apple4(get_apple4),
    	.get_apple5(get_apple5),
		.game_status(game_status),
    	.an(an),
    	.seg(seg)
        );
        
        
     Audio AUD (
         .clk(CLK100MHZ),
         .hit_wall(hit_wall),
         .get_apple(get_apple),
         .get_apple2(get_apple2),
         .get_apple3(get_apple3),
         .get_apple4(get_apple4),
         .get_apple5(get_apple5),
         .hit_itself(hit_itself),
         .up(up),
         .right(right),
         .down(down),
         .left(left),
         .AUD_PWM(AUD_PWM),
         .AUD_SD(AUD_SD)         );
         
     keyboard (
        .clk(CLK100MHZ),
        .rst(1),
        .key_clk(key_clk),
        .key_data(key_data),
        .kup(kup),
        .kdown(kdown),
        .kleft(kleft),
        .kright(kright)
     );
endmodule
