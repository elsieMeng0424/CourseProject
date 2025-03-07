module display(
    input clock, // 148.5MHZ，用于输出1920x1080@60Hz的VGA信号
    input [5:0] apple_x,
    input [5:0] apple_y,
    input [5:0] apple2_x,
    input [5:0] apple2_y,
    input [5:0] apple3_x,
    input [5:0] apple3_y,
    input [5:0] apple4_x,
    input [5:0] apple4_y,
    input [5:0] apple5_x,
    input [5:0] apple5_y,  
    input [5:0] wall_x,
    input [5:0] wall_y,  
    input [5:0] wall2_x,
    input [5:0] wall2_y,
    input [5:0] wall3_x,
    input [5:0] wall3_y,
    input [5:0] wall4_x,
    input [5:0] wall4_y,    
    input [5:0] wall5_x,
    input [5:0] wall5_y,  
    input [5:0] wall6_x,
    input [5:0] wall6_y,
    input [5:0] wall7_x,
    input [5:0] wall7_y,
    input [5:0] wall8_x,
    input [5:0] wall8_y,
    input [32*6-1:0] snake_x_temp,
    input [32*6-1:0] snake_y_temp,
    input [31:0] snake_piece_is_display,
    input [1:0] game_status,
    
    input [2:0] snake_color, //蛇的颜色(低位至高位分别为R、G、B) 
    
    output h_sync,v_sync,
    output reg [11:0] vga
    );
    
    wire VGA_CLK[1:0];
    my_clk_wiz_1 (clock,VGA_CLK[1]);
	localparam PAUSED=2'b00;
    localparam PLAYING=2'b01;
    localparam DIE_FLASHING=2'b10;
    localparam INITIALIZING=2'b11;
  
	localparam UP=2'b00;
    localparam RIGHT=2'b01;
    localparam DOWN=2'b10;
    localparam LEFT=2'b11;
    
    localparam h_active_pixels=1920;
    localparam v_active_pixels=1080;
    
	wire [11:0] x_counter;
	wire [10:0] y_counter;
	wire in_display_area;
	    
	// snake_x[0]：头的横坐标  snake_y[0]:头的纵坐标
    reg [5:0] snake_x [31:0];
	reg [5:0] snake_y [31:0];
	
	// 当前x，y坐标，0<=x<=47,0<=y<=26
	reg [5:0] current_x;
	reg [5:0] current_y;
    
	vga_sync_generator(
	    .clock(VGA_CLK[1]),
	    .h_sync(h_sync),
	    .v_sync(v_sync),
	    .x_counter(x_counter),
	    .y_counter(y_counter),
	    .in_display_area(in_display_area)
	  );	
	 
	
	// 用于模块间传递二维数组 [5:0] snake_x/y [31:0]
	integer i;
	always @(snake_x_temp,snake_y_temp)
	begin
	for (i=0;i<32;i=i+1)
		begin
			// 片选
			snake_x[i]<=snake_x_temp[6*i+:6];
			snake_y[i]<=snake_y_temp[6*i+:6];
		end
	end
	
	always @(x_counter or y_counter)
	begin
		current_x<=x_counter/21;
		current_y<=y_counter/28;
	end 
	
	reg [11:0]RGB_snake_head;
	reg [11:0]RGB_snake_body;	
	
	integer j;
	always @(*)
	begin
	for(j=0;j<12;j=j+1)
	   begin
	   RGB_snake_head[j] = snake_color[j/4];
	   RGB_snake_body[j] = snake_color[j/4];
	   if(j == 2 || j == 6 || j == 10) RGB_snake_head[j] = 1;
	   if(j == 3 || j == 7 || j == 11) RGB_snake_body[j] = 0;
	   end
    end
    
    integer k;    		
    reg flag;
    always @(posedge VGA_CLK[1])
    begin
			begin
			    flag <= 0;
				if (in_display_area==0) vga<=0;
				else if ((game_status==DIE_FLASHING) && (((current_x==8 || current_x==12 || current_x==14 || current_x==16 ||current_x==18 ||current_x==20 ||current_x==22||current_x==27||current_x==29||current_x==35||current_x==39) && (current_y >=11 &&current_y<=15))
				        ||((current_x==23 || current_x==24||current_x==36||current_x==37)&&(current_y==11||current_y==13||current_y==15))
				        ||((current_x==31||current_x==33)&&(current_y>=11 &&current_y<=14))
				        ||((current_y==11)&&(current_x==9||current_x==10||current_x==13||current_x==17||current_x==19||current_x==28||current_x==40||current_x==41))
				        ||(current_x==41&&current_y==12)
				        ||((current_x==10||current_x==13||current_x==40||current_x==41)&&(current_y==13))
				        ||(current_y==14&&(current_x==10||current_x==40))
				        ||((current_x==9||current_x==10||current_x==28||current_x==32||current_x==41)&&current_y==15))) vga<=12'b0000_0000_1111;
				else if ((game_status==DIE_FLASHING) && (current_x>=7 && current_x <= 42 && current_y>=10 && current_y<=16)) vga<=12'b1111_1111_1111;
				else if ((game_status==DIE_FLASHING) && (current_x>=6 && current_x <= 43 && current_y>=9 && current_y<=17)) vga<=12'b0111_0111_0111;
				else if (current_x==0 || current_x==48 || current_y==0 || current_y == 26) vga<=12'b1111_1111_1111; //边框
				else if (current_x==wall_x && current_y==wall_y) vga<=12'b1111_1111_1111;
				else if (current_x==wall2_x && current_y==wall2_y) vga<=12'b1111_1111_1111;
				else if (current_x==wall3_x && current_y==wall3_y) vga<=12'b1111_1111_1111;
				else if (current_x==wall4_x && current_y==wall4_y) vga<=12'b1111_1111_1111;
				else if (current_x==wall5_x && current_y==wall5_y) vga<=12'b1111_1111_1111;
                else if (current_x==wall6_x && current_y==wall6_y) vga<=12'b1111_1111_1111;
                else if (current_x==wall7_x && current_y==wall7_y) vga<=12'b1111_1111_1111;
                else if (current_x==wall8_x && current_y==wall8_y) vga<=12'b1111_1111_1111;
				else if ((current_x == apple_x && current_y == apple_y) || (current_x == apple2_x && current_y == apple2_y)) vga<=12'b0000_0000_1111; //苹果(红色)
				else if (current_x == apple3_x && current_y == apple3_y) vga<=12'b0000_1111_1111;
				else if ((current_x == apple4_x && current_y == apple4_y) || (current_x == apple5_x && current_y == apple5_y)) vga<=12'b0000_0000_1111; //苹果(红色)
				else if (current_x == snake_x[0] && current_y == snake_y[0] && snake_piece_is_display[0]==1) vga <= RGB_snake_head; //蛇头
				else if(game_status==INITIALIZING && ((current_x==16 && current_y==3) || (current_x==16 && current_y==4) || (current_x==16 && current_y==5) || (current_x==16 && current_y==7)
				    || ((current_x==17||current_x==34||current_x==35) && (current_y==3||current_y==5||current_y==7))
				    || (current_x==18 && current_y==3) || (current_x==18 && current_y==5) || (current_x==18 && current_y==6) ||(current_x==18 && current_y==7)
				    || ((current_x==20||current_x==22||current_x==24||current_x==26||current_x==28||current_x==33) && (current_y==3||current_y==4||current_y==5||current_y==6||current_y==7))
				    || ((current_x==21||current_x==25||current_x==31) && current_y==3) || (current_x==25 && current_y==5) || (current_x==30&&current_y==4)
				    || (current_x==30&&current_y==6) || (current_x==31 && current_y==7) || (current_x==29&&current_y==5))) vga<=12'b1111_0000_1111; 
				else begin
				    for(k=0;k<32;k=k+1)
				        begin
				        if(current_x == snake_x[k] && current_y == snake_y[k] && snake_piece_is_display[k] == 1) flag = 1;
				        end
				     if(flag == 1) vga <= RGB_snake_body;
				     else vga <= 0;
				 end
			end
    end
endmodule