#include <conio.h>
#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// �˿�����в�������������ҵ�������޸�

void wait_for_enter()
{
    cout << endl
        << "���س�������";
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
    cout << "*      1 ����ӷ�      2 ��������      3 ����ת��          *" << endl;
    cout << "*      4 ����˷�      5 Hadamard�˻�  6 ������          *" << endl;
    cout << "*      7 ���Ӧ��      8 OSTU�㷨      0 �˳�ϵͳ          *" << endl;
    for (int i = 0; i < 60; i++)
        cout << '*';
    cout << endl;
}

void input_rac(int *p_row,int *p_column)
{
    cout << "���������������Լ�������" << endl;
    while (1) {
        cin >> *p_row >> *p_column;
        if (!cin.good()) {
            cout << "�����������������룺" << endl;
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
            cout << "�����������������룺" << endl;
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
            cout << "�����������������룺" << endl;
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
            cout << "�����������������룺" << endl;
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
    // /* ��vs2019+opencv��ȷ���ú󷽿�ʹ�ã��˴�ֻ����һ�ζ�ȡ����ʾͼ��Ĳο����룬���๦������������ƺͲ������� */
     Mat image =
         imread("demolena.jpg", IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
     imshow("Image-original", image);
     
     
    // ��ʾ��Mat��ʽ���������໥ת��
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
    
     output_image(image.rows, image.cols, B1, A, "B1���");
     output_image(image.rows, image.cols, B2, A, "B2���");
     output_image(image.rows, image.cols, B3, A, "B3���");
     output_image(image.rows, image.cols, B4, A, "B4���");
     output_image(image.rows, image.cols, B5, A, "B5���");
     output_image(image.rows, image.cols, B6, A, "B6���");
     waitKey(0);
     delete[]A;
}

void OSTU_output(const char* ch)
{
    system("cls");
    Mat image =
        imread(ch, IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
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
        imread(ch, IMREAD_GRAYSCALE); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
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
    cout << "���������" << row << "��" << column << "�еľ���A��" << endl;
    double** A = new double* [row];
    double** B = new double* [row];
    for (int i = 0; i < row; i++) {
        A[i] = new double[column];
        B[i] = new double[column];
    }
    input_matrix(A, row, column);
    cout << "���������" << row << "��" << column << "�еľ���B��" << endl;
    input_matrix(B, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] += B[i][j];

    cout << "����C=A+BΪ��" << endl;
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
    cout << "���������" << row << "��" << column << "�еľ���A��" << endl;
    input_matrix(A, row, column);
    cout << "��������֮��˵�ʵ��k��" << endl;
    input_k(p_k);
    
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] *= k;

    cout << "����k*AΪ��" << endl;
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
        
    cout << "���������" << row << "��" << column << "�еľ���A��" << endl;
    input_matrix(A, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            B[j][i] = A[i][j];

    cout << "����A��ת��Ϊ��" << endl;
    output_matrix(B, column, row);
    delete[]A;
    delete[]B;
}

void matrimulti()
{
    system("cls");
    int row1, column1, row2, column2, * p_r1 = &row1, * p_r2 = &row2, * p_c1 = &column1, * p_c2 = &column2;

    while (1) {
        cout << "���ľ���" << endl;
        input_rac(p_r1, p_c1);
        double** A = new double* [row1];
        for (int i = 0; i < row1; i++) {
            A[i] = new double[column1];
        }
        cout << "���������" << row1 << "��" << column1 << "�еľ���A��" << endl;
        input_matrix(A, row1, column1);

        cout << "�Ҳ�ľ���" << endl;
        input_rac(p_r2, p_c2);
        double** B = new double* [row2];
        for (int i = 0; i < row2; i++) {
            B[i] = new double[column2];
        }
        cout << "���������" << row2 << "��" << column2 << "�еľ���B��" << endl;
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

            cout << "����A�����B�ĳ˻�����Ϊ��" << endl;
            output_matrix(C, row1, column2);
            delete[]A;
            delete[]B;
            delete[]C;
            break;
        }

        cout << "������������������Ҳ���������������������" << endl;
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
    cout << "���������" << row << "��" << column << "�еľ���A��" << endl;
    input_matrix(A, row, column);
    cout << "���������" << row << "��" << column << "�еľ���B��" << endl;
    input_matrix(B, row, column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            A[i][j] *= B[i][j];

    cout << "����C=A+BΪ��" << endl;
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
    cout << "���������" << row << "��" << column << "�еľ���A��" << endl;
    input_matrix_with_padding(A, row, column);
    cout << "������Kernel����(3x3):" << endl;
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

    cout << "����A�ľ��������Ϊ��" << endl;
    output_matrix(B, row, column);
    delete[]A;
    delete[]B;
    delete[]K;
}

int main()
{
    char choice, ch;// ������ر���

    wait_for_enter();
    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������

        menu(); // ���ò˵���ʾ���������в������

        choice = _getch();// ��Ҫ������˵�ѡ����choice

        if (choice == '0') // ѡ���˳�
        {
            cout << "\n ȷ���˳���?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // ���������������������Ʋ���ɣ����������������������͵ȣ�����ѡ��ӷ�������в���
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
                cout << "\n ����������������" << endl;
                wait_for_enter();
        }
        wait_for_enter();
    }
    return 0;
}