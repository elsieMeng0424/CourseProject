#include <conio.h>
#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 此框架若有不完美可以在作业中任意修改

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

void menu()
{
    for (int i = 0; i < 60; i++)
        cout << '*';
    cout << endl;
    cout << "*      1 矩阵加法      2 矩阵数乘      3 矩阵转置          *" << endl;
    cout << "*      4 矩阵乘法      5 Hadamard乘积  6 矩阵卷积          *" << endl;
    cout << "*      7 卷积应用      8 OSTU算法      0 退出系统          *" << endl;
    for (int i = 0; i < 60; i++)
        cout << '*';
    cout << endl;
}

void input_rac(int *p_row,int *p_column)
{
    cout << "请输入矩阵的行数以及列数：" << endl;
    while (1) {
        cin >> *p_row >> *p_column;
        if (!cin.good()) {
            cout << "输入有误，请重新输入：" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
            break;
    }
    cin.clear();
    cin.ignore(1024, '\n');
}

void input_k(double* p_k)
{
    while (1) {
        cin >> *p_k;
        if (!cin.good()) {
            cout << "输入有误，请重新输入：" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
            break;
    }
    cin.clear();
    cin.ignore(1024, '\n');
}

void input_matrix(double** A, int row, int column)
{
    int i, j;
    while (1) {
        for (i = 0; i < row; i++)
            for (j = 0; j < column; j++)
                cin >> A[i][j];
        if (!cin.good()) {
            cout << "输入有误，请重新输入：" << endl;
            cin.clear();
            cin.ignore(1024,'\n');
        }
        else
            break;
    }
    cin.clear();
    cin.ignore(1024, '\n');
}

void output_matrix(double** A, int row, int column)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            cout << setw(7) << A[i][j] << ' ';
        cout << endl;
    }
}

void input_matrix_with_padding(double** A, int row, int column)
{
    for (int i = 0; i < row + 2; i++)
        for (int j = 0; j < column + 2; j++)
            A[i][j] = 0;
    while (1) {
        for (int i = 1; i < row+1; i++)
            for (int j = 1; j < column+1; j++)
                cin >> A[i][j];
        if (!cin.good()) {
            cout << "输入有误，请重新输入：" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
            break;
    }
    cin.clear();
    cin.ignore(1024, '\n');

}

double calculate_convolution(double** A, double** K, int i0, int j0)
{
    double sum = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            sum += (K[i][j] * A[i0 + i][j0 + j]);
    return sum;
}

int calculate_convolution(int **A, int K[3][3], int i0, int j0)
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            sum += (K[i][j] * A[i0 + i][j0 + j]);
    return sum;
}

void output_image(int row, int column, int K[3][3], int **A,const char ch[])
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            sum += K[i][j];
    if (sum == 0)
        sum = 1;
    int** B = new int* [row];
    for (int i = 0; i < row; i++)
        B[i] = new int[column];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++) {
            B[i][j] = calculate_convolution(A, K, i, j)/sum;
            if (B[i][j] < 0)
                B[i][j] = 0;
            if (B[i][j] > 255)
                B[i][j] = 255;
        }
    Mat image1(row, column, CV_8UC1);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            image1.at<uchar>(i, j) = B[i][j];
    imshow(ch, image1);
    delete[]B;
}

void demo()
{
    // /* 对vs2019+opencv正确配置后方可使用，此处只给出一段读取并显示图像的参考代码，其余功能流程自行设计和查阅文献 */
     Mat image =
         imread("demolena.jpg", IMREAD_GRAYSCALE); // 图像的灰度值存放在格式为Mat的变量image中
     imshow("Image-original", image);
     
     
    // 提示：Mat格式可与数组相互转换
     int B1[3][3] = { 1,1,1,1,1,1,1,1,1 }, B2[3][3] = { -1,-2,-1,0,0,0,1,2,1 }, B3[3][3] = { -1,0,1,-2,0,2,-1,0,1 },
         B4[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 }, B5[3][3] = { -1,-1,0,-1,0,1,0,1,1 }, B6[3][3] = { 1,2,1,2,4,2,1,2,1 };
     int** A = new int* [image.rows + 2];
     for (int i = 0; i < image.rows+2; i++) 
         A[i] = new int[image.cols+2];    
     for (int i = 0; i < image.rows +2; i++)
         for (int j = 0; j < image.cols + 2; j++)
             A[i][j] = 0;
     for (int i = 1; i < image.rows+1; i++)
         for (int j = 1; j < image.cols+1; j++)
             A[i][j] = image.at<uchar>(i-1,j-1);
    
     output_image(image.rows, image.cols, B1, A, "B1卷积");
     output_image(image.rows, image.cols, B2, A, "B2卷积");
     output_image(image.rows, image.cols, B3, A, "B3卷积");
     output_image(image.rows, image.cols, B4, A, "B4卷积");
     output_image(image.rows, image.cols, B5, A, "B5卷积");
     output_image(image.rows, image.cols, B6, A, "B6卷积");
     waitKey(0);
     delete[]A;
}

void OSTU_output(const char* ch)
{
    system("cls");
    Mat image =
        imread(ch, IMREAD_GRAYSCALE); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original", image);
    
    int sum = image.rows * image.cols;
    int* array = new int[sum * sizeof(int)];
    int k = 0;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            array[k] = image.at<uchar>(i, j);
            k++;
            if (array[k] > 255)
                array[k] = 255;
            if (array[k] < 0)
                array[k] = 0;
        }
    }
    int statics[256] = {0};
    double frq[256];
    for (int i = 0; i < sum; i++) {
        statics[array[i]]++;
    }

    for (int i = 0; i < 256; i++)
        frq[i] = double(statics[i]) / sum;

    double g0 = 0;
    int i_max = 0;
    for (int i = 0; i < 256; i++) {
        double w0 = 0, u0 = 0, w1 = 0, u1 = 0;
        for (int j = 0; j <= i; j++) {
            w0 += frq[j];
            u0 += j * frq[j];
        }
        u0 = u0 / w0;
        for (int j = i + 1; j < 256; j++) {
            w1 += frq[j];
            u1 += j * frq[j];
        }
        u1 = u1 / w1;
        double g = w0 * w1 * (u0 - u1) * (u0 - u1);
        if (g > g0) {
            g0 = g;
            i_max = i;
        }
    }
    for (int i = 0; i < sum; i++) {
        if (array[i] <= i_max)
            array[i] = 0;
        else
            array[i] = 255;
    }
    Mat image1(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
            image1.at<uchar>(i, j) = array[i * image.cols + j];
    imshow("Result", image1);
    delete []array;
}

void OSTU_forSnowball(const char* ch)
{
    system("cls");
    Mat image =
        imread(ch, IMREAD_GRAYSCALE); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original", image);

    int sum = image.rows * image.cols;
    int* array = new int[sum * sizeof(int)];
    int k = 0;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            array[k] = image.at<uchar>(i, j);
            k++;
            if (array[k] > 255)
                array[k] = 255;
            if (array[k] < 0)
                array[k] = 0;
        }
    }
    int statics[256] = { 0 };
    double frq[256];
    for (int i = 0; i < sum; i++) {
        statics[array[i]]++;
    }

    for (int i = 0; i < 256; i++)
        frq[i] = double(statics[i]) / sum;

    double g0 = 0;
    int i_max = 0;
    for (int i = 0; i < 256; i++) {
        double w0 = 0, u0 = 0, w1 = 0, u1 = 0;
        for (int j = 0; j <= i; j++) {
            w0 += frq[j];
            u0 += j * frq[j];
        }
        u0 = u0 / w0;
        for (int j = i + 1; j < 256; j++) {
            w1 += frq[j];
            u1 += j * frq[j];
        }
        u1 = u1 / w1;
        double g = w0 * w1 * (u0 - u1) * (u0 - u1);
        if (g > g0) {
            g0 = g;
            i_max = i;
        }
    }
    for (int i = 0; i < sum; i++) {
        if (array[i] <= i_max)
            array[i] = 0;
    }
    Mat image1(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
            image1.at<uchar>(i, j) = array[i * image.cols + j];
    imshow("Result", image1);
    delete[]array;
}
void OSTU()
{
    OSTU_output("demolena.jpg");
    waitKey(0);
    OSTU_output("brain.jpg");
    waitKey(0);
    OSTU_output("polyhedrosis.jpg");
    waitKey(0);
    OSTU_output("ship.jpg");
    waitKey(0);
    OSTU_forSnowball("snowball.jpg");
    waitKey(0);
}
void matriplus()
{
    system("cls");
    int row, column, * p_row = &row, * p_column = &column;

    input_rac(p_row,p_column);
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵A：" << endl;
    double** A = new double* [row];
    double** B = new double* [row];
    for (int i = 0; i < row; i++) {
        A[i] = new double[column];
        B[i] = new double[column];
    }
    input_matrix(A, row, column);
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵B：" << endl;
    input_matrix(B, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] += B[i][j];

    cout << "矩阵C=A+B为：" << endl;
    output_matrix(A, row, column);

    delete[]A;
    delete[]B;
}

void nummulti()
{
    system("cls");
    int row, column, * p_row = &row, * p_column = &column;
    double k, * p_k = &k;

    input_rac(p_row, p_column);
    double** A = new double* [row];
    for (int i = 0; i < row; i++) {
        A[i] = new double[column];
    }
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵A：" << endl;
    input_matrix(A, row, column);
    cout << "请输入与之相乘的实数k：" << endl;
    input_k(p_k);
    
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] *= k;

    cout << "矩阵k*A为：" << endl;
    output_matrix(A, row, column);
    delete[]A;
}

void matritrans()
{
    
    system("cls");
    int row, column, * p_row = &row, * p_column = &column;

    input_rac(p_row, p_column);
    double** A = new double* [row];
    double** B = new double* [column];
    for (int i = 0; i < row; i++) 
        A[i] = new double[column];
    for (int i = 0; i < column; i++)
        B[i] = new double[row];
        
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵A：" << endl;
    input_matrix(A, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            B[j][i] = A[i][j];

    cout << "矩阵A的转置为：" << endl;
    output_matrix(B, column, row);
    delete[]A;
    delete[]B;
}

void matrimulti()
{
    system("cls");
    int row1, column1, row2, column2, * p_r1 = &row1, * p_r2 = &row2, * p_c1 = &column1, * p_c2 = &column2;

    while (1) {
        cout << "左侧的矩阵：" << endl;
        input_rac(p_r1, p_c1);
        double** A = new double* [row1];
        for (int i = 0; i < row1; i++) {
            A[i] = new double[column1];
        }
        cout << "请输入矩阵" << row1 << "行" << column1 << "列的矩阵A：" << endl;
        input_matrix(A, row1, column1);

        cout << "右侧的矩阵：" << endl;
        input_rac(p_r2, p_c2);
        double** B = new double* [row2];
        for (int i = 0; i < row2; i++) {
            B[i] = new double[column2];
        }
        cout << "请输入矩阵" << row2 << "行" << column2 << "列的矩阵B：" << endl;
        input_matrix(B, row2, column2);

        if (column1 == row2) {
            double** C = new double* [row1];
            for (int i = 0; i < row1; i++)
                C[i] = new double[column2];
            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < column2; j++) {
                    C[i][j] = 0;
                    for (int k = 0; k < row2; k++)
                        C[i][j] += (A[i][k] * B[k][j]);
                }
            }

            cout << "矩阵A与矩阵B的乘积矩阵为：" << endl;
            output_matrix(C, row1, column2);
            delete[]A;
            delete[]B;
            delete[]C;
            break;
        }

        cout << "左侧矩阵的列数不等于右侧矩阵的行数，请重新输入" << endl;
        delete[]A;
        delete[]B;
    }
}

void hadamulti()
{
    system("cls");
    int row, column, * p_row = &row, * p_column = &column;

    input_rac(p_row, p_column);
    double** A = new double* [row];
    double** B = new double* [row];
    for (int i = 0; i < row; i++) {
        A[i] = new double[column];
        B[i] = new double[column];
    }
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵A：" << endl;
    input_matrix(A, row, column);
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵B：" << endl;
    input_matrix(B, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] *= B[i][j];

    cout << "矩阵C=A+B为：" << endl;
    output_matrix(A, row, column);
    delete[]A;
    delete[]B;
}

void conv()
{
    system("cls");
    int row, column, * p_row = &row, * p_column = &column;

    input_rac(p_row, p_column);
    double** A = new double* [row+2];
    for (int i = 0; i < row + 2; i++)
        A[i] = new double[column + 2];
    cout << "请输入矩阵" << row << "行" << column << "列的矩阵A：" << endl;
    input_matrix_with_padding(A, row, column);
    cout << "请输入Kernel矩阵(3x3):" << endl;
    double** K = new double*[3];
    for (int i = 0; i < 3; i++)
        K[i] = new double[3];
    input_matrix(K, 3, 3);

    double** B = new double* [row];
    for (int i = 0; i < row; i++)
        B[i] = new double[column];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            B[i][j] = calculate_convolution(A, K, i, j);

    cout << "矩阵A的卷积计算结果为：" << endl;
    output_matrix(B, row, column);
    delete[]A;
    delete[]B;
    delete[]K;
}

int main()
{
    char choice, ch;// 定义相关变量

    wait_for_enter();
    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数

        menu(); // 调用菜单显示函数，自行补充完成

        choice = _getch();// 按要求输入菜单选择项choice

        if (choice == '0') // 选择退出
        {
            cout << "\n 确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // 下述矩阵操作函数自行设计并完成（包括函数参数及返回类型等），若选择加分项，请自行补充
            case '1':
                matriplus();
                break;
            case '2':
                nummulti();
                break;
            case '3':
                matritrans();
                break;
            case '4':
                matrimulti();
                break;
            case '5':
                hadamulti();
                break;
            case '6':
                conv();
                break;
            case '7':
                demo();
                break;
            case '8':
                OSTU();
                break;
            default:
                cout << "\n 输入错误，请从新输入" << endl;
                wait_for_enter();
        }
        wait_for_enter();
    }
    return 0;
}