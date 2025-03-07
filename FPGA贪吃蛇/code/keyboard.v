module keyboard (clk,rst,key_clk,key_data,kup,kdown,kleft,kright);
input clk;                 //系统时钟
input rst;				   //系统复位，低有效
input key_clk;             //PS2键盘时钟
input key_data;	           //PS2键盘数据输入
output reg kup,kdown,kleft,kright;

reg [3:0] now_bit = 0;        //记录已获取的bit数
reg [7:0] store = 0;          //存储键盘数据输入
reg [7:0] key_info = 0;       //存储键盘数据信息
reg break = 0;                //断码标志

reg	key_clk_new = 1'b1, key_clk_old = 1'b1; 
reg	key_data_new = 1'b1, key_data_old = 1'b1;

// 对键盘时钟数据信号进行延时锁存
always @ (posedge clk or negedge rst)
begin
	if(!rst) 
	begin
		key_clk_new <= 1'b1;
		key_clk_old <= 1'b1;
		key_data_new <= 1'b1;
		key_data_old <= 1'b1;
	end
	else
	begin
		//交替存储实现延时锁存
    	key_clk_new <= key_clk;
		key_clk_old <= key_clk_new;
		key_data_new <= key_data;
		key_data_old <= key_data_new;
	end
end

wire key_clk_neg = key_clk_old & (~key_clk_new); 

//PS2键盘时钟信号下降沿读取数据
always @ (posedge clk or negedge rst)
begin
	if(!rst) 
	begin
		now_bit <= 4'd0;
		store <= 8'd0;
	end
	else
	begin
		if(key_clk_neg)
		begin
			if(now_bit >= 4'd10) now_bit <= 4'd0;
			else now_bit <= now_bit + 1'b1;
			case (now_bit)
				0: ;	                    //起始位
				// bit数据位
				1: store[0] <= key_data_old;
				2: store[1] <= key_data_old;
				3: store[2] <= key_data_old;
				4: store[3] <= key_data_old;
				5: store[4] <= key_data_old;
				6: store[5] <= key_data_old;
				7: store[6] <= key_data_old;
				8: store[7] <= key_data_old;
				9: ;	                    //校验位
				10:;	                    //结束位
				default: ;
			endcase
		end
	end
end

//判断断码
always @ (posedge clk or negedge rst)
begin
	if(!rst) 
	begin
		break <= 0;       //重置标记
		key_info <= 0;
	end
	else
	begin
		if(now_bit == 4'd10 && key_clk_neg)       //已经读取完整段数据，且处于PS2键盘时钟信号下降沿
		begin
			if(store == 8'hf0) break <= 1;        //断码（8'hf0）表示按键松开，下一个数据为断码，设置断码标示为1
			else if(!break) key_info <= store;    //不为断码
			else                                  //该段数据是断码，舍弃
			begin
				break <= 0;       //重置标记
				key_info <= 0;
			end
		end
	end
end


//将从键盘得到的数据转换为ASCII码
always @ (key_info)
begin
    kup=0;
    kdown=0;
    kleft=0;
    kright=0;
    case (key_info)
        8'h75: kup <= 1;			//上箭头
		8'h72: kdown <= 1;			//下箭头
		8'h6b: kleft <= 1;			//左箭头
		8'h74: kright <= 1;			//右箭头
		8'h1d: kup <= 1;   		// w
		8'h1b: kdown <= 1;   		// s
		8'h1c: kleft <= 1;   		// a
		8'h23: kright <= 1;   		// d
    endcase
end

endmodule