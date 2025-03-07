`timescale 1ns / 1ps
module snake(
	input clock,
	input [2:0]speed,
	input [1:0] next_direction,
	input [1:0] game_status,
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
    	
	output reg [1:0] current_direction,
    output [32*6-1:0] snake_x_temp,
	output [32*6-1:0] snake_y_temp,
	output reg [31:0] snake_piece_is_display, // �������峤
	output reg get_apple,
	output reg get_apple2,
	output reg get_apple3,
	output reg get_apple4,
	output reg get_apple5,
	output reg hit_wall,
	output reg hit_itself
    );
    
    wire is_pause;
    assign is_pause = (speed == 0) ? 1'b1 : 1'b0;
    
    reg [25:0] count;
    reg [25:0] count_two;
    reg [31:0] snake_piece_is_display_origin; // �洢�峤�ľ�ֵ������������˸
    
	localparam PAUSED=2'b00;
    localparam PLAYING=2'b01;
    localparam DIE_FLASHING=2'b10;
    localparam INITIALIZING=2'b11;

    localparam UP=2'b00;
    localparam RIGHT=2'b01;
    localparam DOWN=2'b10;
    localparam LEFT=2'b11;
    
	// snake_x[0]��ͷ�ĺ�����  snake_y[0]:ͷ��������
    reg [5:0] snake_x [31:0];
    reg [5:0] snake_y [31:0];


	// ����ģ��䴫�ݶ�ά���� [5:0] snake_x/y [31:0]
	// �ο��� https://stackoverflow.com/questions/16369698/how-to-pass-array-structure-between-two-verilog-modules
    genvar i;
    generate for (i=0;i<32;i=i+1)
    begin
    	assign snake_x_temp[6*i+:6]=snake_x[i];
    	assign snake_y_temp[6*i+:6]=snake_y[i];
   	end endgenerate
   	
   	
	initial
   	begin
   	count<=0;
   	count_two<=0;
   	end
   	
   	integer k;
   	integer hitflag;
    always @(posedge clock)
    begin
        hitflag=0;
    	if (count_two>=40000000) count_two<=0;
    	else count_two<=count_two+1;
    	
    	if (game_status==INITIALIZING)
    	begin
		snake_piece_is_display<=32'b00000000_00000000_00000000_00000111;
    	snake_x[0]<=14;
    	snake_y[0]<=20;
    	snake_x[1]<=13;
    	snake_y[1]<=20;
    	snake_x[2]<=12;
    	snake_y[2]<=20;
    	current_direction<=RIGHT;
    	hit_wall<=0;
    	hit_itself<=0;
    	end
    	
    	else if (game_status==DIE_FLASHING)
    	begin
    	// ��˸
    	if (count_two==20000000) snake_piece_is_display<=0;
    	else if (count_two==0) snake_piece_is_display<=snake_piece_is_display_origin;
    	end
    	
    	else if (game_status==PLAYING && (is_pause == 0))
    	begin
    		snake_piece_is_display_origin<=snake_piece_is_display; // �洢�峤�ľ�ֵ������������˸(������)
    		
    		if (snake_x[0]==0 || snake_x[0]==47 || snake_y[0]==0 || snake_y[0]==26) hit_wall<=1;
    		else if(snake_x[0] == wall_x && snake_y[0] == wall_y) hit_wall<=1;
    		else if(snake_x[0] == wall2_x && snake_y[0] == wall2_y) hit_wall<=1;
    		else if(snake_x[0] == wall3_x && snake_y[0] == wall3_y) hit_wall<=1;
    		else if(snake_x[0] == wall4_x && snake_y[0] == wall4_y) hit_wall<=1;
    		else if(snake_x[0] == wall5_x && snake_y[0] == wall5_y) hit_wall<=1;
            else if(snake_x[0] == wall6_x && snake_y[0] == wall6_y) hit_wall<=1;
            else if(snake_x[0] == wall7_x && snake_y[0] == wall7_y) hit_wall<=1;
            else if(snake_x[0] == wall8_x && snake_y[0] == wall8_y) hit_wall<=1;
    		else hit_wall<=0; // �Ƿ�ײǽ
    		for(k = 1; k < 32; k= k+1) begin
    		    if(snake_x[0]==snake_x[k] && snake_y[0]==snake_y[k] && snake_piece_is_display[k]==1) hitflag=1;
    		    end
    		if(hitflag==1) hit_itself<=1;
    		else hit_itself<=0; // �Ƿ�ײ�Լ�
    		
    		if (snake_x[0]==apple_x && snake_y[0]==apple_y) get_apple<=1;
    		else get_apple<=0; // �Ƿ�Ե�ƻ��
    		if(snake_x[0]==apple2_x && snake_y[0]==apple2_y) get_apple2<=1;
    		else get_apple2<=0;
    		if(snake_x[0]==apple3_x && snake_y[0]==apple3_y) get_apple3<=1;
    		else get_apple3<=0;
    		if(snake_x[0]==apple4_x && snake_y[0]==apple4_y) get_apple4<=1;
            else get_apple4<=0;
            if(snake_x[0]==apple5_x && snake_y[0]==apple5_y) get_apple5<=1;
            else get_apple5<=0;
    		
    		if (get_apple == 1 ) 
    		begin
    		snake_piece_is_display<=2*snake_piece_is_display+1; // �����峤����snake_piece_is_display���һ��0���1��
    		get_apple<=0;
    		end

    		if(get_apple2 == 1)
    		begin
    		snake_piece_is_display<=2*snake_piece_is_display+1;
    		get_apple2<=0;
    		end
    		
    		if(get_apple3 == 1)
            begin
            snake_piece_is_display<=2*snake_piece_is_display+1;
            get_apple3<=0;
            end    		
            
            if(get_apple4 == 1)
            begin
            snake_piece_is_display<=2*snake_piece_is_display+1;
            get_apple4<=0;
            end
            
            if(get_apple5 == 1)
            begin
            snake_piece_is_display<=2*snake_piece_is_display+1;
            get_apple5<=0;
            end 
    		
    		current_direction<=next_direction; // ���·���
    		
    		if(is_pause == 1)
    		    count <= count;
    		else if (count < 5*1000000*(8 - speed)) // �����ٶ�
    			count <= count+1;
    		else
    		begin
				count <= 0;
				
				// ͷǰ��
				case (next_direction)
				UP:
					begin
					snake_x[0]<=snake_x[0];
					snake_y[0]<=snake_y[0]-1;
					end
				RIGHT:
					begin
					snake_x[0]<=snake_x[0]+1;
					snake_y[0]<=snake_y[0];
					end
				DOWN:
					begin
					snake_x[0]<=snake_x[0];
					snake_y[0]<=snake_y[0]+1;
					end
				LEFT:
					begin
					snake_x[0]<=snake_x[0]-1;
					snake_y[0]<=snake_y[0];
					end
				default:
					begin
					snake_x[0]<=snake_x[0]+1;
					snake_y[0]<=snake_y[0];
					end
				endcase
				
				// ����ǰ��
				snake_x[1]<=snake_x[0];
				snake_y[1]<=snake_y[0];
	
				snake_x[2]<=snake_x[1];
				snake_y[2]<=snake_y[1];
	
				snake_x[3]<=snake_x[2];
				snake_y[3]<=snake_y[2];
	
				snake_x[4]<=snake_x[3];
				snake_y[4]<=snake_y[3];
	
				snake_x[5]<=snake_x[4];
				snake_y[5]<=snake_y[4];
	
				snake_x[6]<=snake_x[5];
				snake_y[6]<=snake_y[5];
	
				snake_x[7]<=snake_x[6];
				snake_y[7]<=snake_y[6];
	
				snake_x[8]<=snake_x[7];
				snake_y[8]<=snake_y[7];
	
				snake_x[9]<=snake_x[8];
				snake_y[9]<=snake_y[8];
	
				snake_x[10]<=snake_x[9];
				snake_y[10]<=snake_y[9];
	
				snake_x[11]<=snake_x[10];
				snake_y[11]<=snake_y[10];
	
				snake_x[12]<=snake_x[11];
				snake_y[12]<=snake_y[11];
	
				snake_x[13]<=snake_x[12];
				snake_y[13]<=snake_y[12];
	
				snake_x[14]<=snake_x[13];
				snake_y[14]<=snake_y[13];
	
				snake_x[15]<=snake_x[14];
				snake_y[15]<=snake_y[14];
	
				snake_x[16]<=snake_x[15];
				snake_y[16]<=snake_y[15];
	
				snake_x[17]<=snake_x[16];
				snake_y[17]<=snake_y[16];
	
				snake_x[18]<=snake_x[17];
				snake_y[18]<=snake_y[17];
	
				snake_x[19]<=snake_x[18];
				snake_y[19]<=snake_y[18];
	
				snake_x[20]<=snake_x[19];
				snake_y[20]<=snake_y[19];
	
				snake_x[21]<=snake_x[20];
				snake_y[21]<=snake_y[20];
	
				snake_x[22]<=snake_x[21];
				snake_y[22]<=snake_y[21];
	
				snake_x[23]<=snake_x[22];
				snake_y[23]<=snake_y[22];
	
				snake_x[24]<=snake_x[23];
				snake_y[24]<=snake_y[23];
	
				snake_x[25]<=snake_x[24];
				snake_y[25]<=snake_y[24];
	
				snake_x[26]<=snake_x[25];
				snake_y[26]<=snake_y[25];
	
				snake_x[27]<=snake_x[26];
				snake_y[27]<=snake_y[26];
	
				snake_x[28]<=snake_x[27];
				snake_y[28]<=snake_y[27];
	
				snake_x[29]<=snake_x[28];
				snake_y[29]<=snake_y[28];
	
				snake_x[30]<=snake_x[29];
				snake_y[30]<=snake_y[29];
	
				snake_x[31]<=snake_x[30];
				snake_y[31]<=snake_y[30];
			end
    	end
    end
endmodule