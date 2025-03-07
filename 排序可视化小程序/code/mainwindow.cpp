#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QLineEdit>
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sort Visualizer"); // 设置窗口标题
    setWindowIcon(QIcon(":/images/images/logoSort.png")); // 设置图标
    resize(1500,900); // 设置窗口大小

    inputMap = QPixmap(230,900); // 初始化inputMap

    // 初始化排序信息
    sortInfoMap = QPixmap(1270,150); // 初始化sortInfoMap
    sortInfo = new SortInfo(INSERTION); // 默认设置为直接插入排序

    // 初始化数组
    arr = new Array; // 初始化数组对象
    arr_ = new Array; // 用于快速排序
    arrInfoMap = QPixmap(150,50); // 初始化arrInfoMap
    arrInfoMap.fill(Qt::gray);
    arrElemMap = QPixmap(1270,50);

    // 初始化排序类
    sorts = new Sorts;

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setGeometry(250, 180, 1230, 650);

    flag = true;

    bars = new BarList; // 初始化长方形链表对象
    record = new recordList; // 初始化记录链表对象

    timer = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateBars()
{
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen(); // 计算宽度
    int gap = width / 20; // 计算间隙
    int maxheight = 640; // 设置最大高度
    int startX = gap;
    for(int k = 0; k < arr->getLen(); k++){
        int height = maxheight * arr->getKth(k) / maxValue; // 计算每个长方形的高度
        QGraphicsRectItem *bar = scene->addRect(startX,650-height,width-2*gap,height);
        bar->setBrush(QColor(167,204,237));
        barItem *bi = new barItem(bar, NULL);
        //bars.append(bar);
        bars->addBar(bi); // 添加到链表中
        startX += width;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QColor color(255,255,255); // 背景色设置为白色
    painter.setBrush(color);
    painter.drawRect(this->rect());

    // 绘制输入框
    QPainter inputPainter(&inputMap);
    QColor inputColor(84, 94, 117);
    inputPainter.setBrush(inputColor);
    inputPainter.drawRect(0,0,230,900);
    painter.drawPixmap(0,0,inputMap);

    // 绘制排序信息
    QPainter sortInfoPainter(&sortInfoMap);
    QColor sortInfoColor(142,172,205);
    sortInfoPainter.setBrush(sortInfoColor);
    sortInfoPainter.drawRect(0,0,1270,150);
    QFont font("楷体", 12); // 设置字体
    sortInfoPainter.setFont(font);
    sortInfo->paint(sortInfoPainter, sorts->getTime(), sorts->getTimeSwap());
    painter.drawPixmap(230,0,sortInfoMap);

//    // 绘制数组长度信息
//    QPainter arrInfoPainter(&arrInfoMap);
//    arrInfoPainter.setBrush(sortInfoColor);
//    arrInfoPainter.drawRect(0,0,150,200);
//    arr->paintText(arrInfoPainter);
//    painter.drawPixmap(1000,20,arrInfoMap);

    //绘制数组元素信息
    if(arr->isReady()){
        QPainter arrElemPainter(&arrElemMap);
        arrElemPainter.setBrush(QColor(99,173,242));
        arrElemPainter.drawRect(0,0,1270,50);
        arr->paintElemText(arrElemPainter);
        painter.drawPixmap(230,850,arrElemMap);
    }

}

void MainWindow::on_insertionBtn_clicked()
{
    if(!timer){
        sortInfo->change(INSERTION);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_binaryBtn_clicked()
{
    if(!timer){
        sortInfo->change(BINARYINSERTION);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_shellBtn_clicked()
{
    if(!timer){
        sortInfo->change(SHELL);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_bubbleBtn_clicked()
{
    if(!timer){
        sortInfo->change(BUBBLE);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_quickBtn_clicked()
{
    if(!timer){
        sortInfo->change(QUICK);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_selectBtn_clicked()
{
    if(!timer){
        sortInfo->change(SELECT);
        sorts->reSet();
        update();
    }
}


void MainWindow::on_setNumBtn_clicked()
{
    if(!timer){
        // 设置数组长度
        QString str = ui->numEdit->toPlainText();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        int n = str.toInt();
        arr->changeNum(n);
        update();
        QApplication::restoreOverrideCursor();
    }
}


void MainWindow::on_randomInitBtn_clicked()
{
    if(!timer){
        // 随机生成数组
        arr->changeNum(arr->getLen());
        arr->randomInit(arr->getLen());
        if(arr->isReady()){
            sorts->reSet();
            scene->clear();
            //bars.clear();
            bars->clear();
            generateBars();
            update();
        }
    }
}


void MainWindow::on_setElemBtn_clicked()
{
    if(!timer){
        // 设置数组元素
        const QString str = ui->elemEdit->toPlainText();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::restoreOverrideCursor();
        arr->changeElem(str);
        if(arr->isReady()){
            sorts->reSet(); // 重置排序对象
            scene->clear(); // 清空长方形框
            //bars.clear();
            bars->clear(); // 清空长方形链表
            generateBars();
            update();
        }
    }
}


void MainWindow::on_sortBtn_clicked()
{
    //sorts->reSet();
    //sorts->sort(*sortInfo, *arr);
    //scene->clear();
    //bars.clear();
    //generateBars();
    //update();
    //sorts->insertionSortPaint(*arr,bars,this);
    if(!timer){
        timer = new QTimer(this); // 初始化计时器类
        sorts->reSet();
        if(sortInfo->type == INSERTION ){
            i = 1;
            connect(timer, &QTimer::timeout, this, &MainWindow::insertionSortStep);
        }
        else if(sortInfo->type == BINARYINSERTION){
            i = 1;
            connect(timer, &QTimer::timeout, this, &MainWindow::binaryInsertionSortStep);
        }
        else if(sortInfo->type == SELECT){
            i = 0;
            connect(timer, &QTimer::timeout, this, &MainWindow::selectSortStep);
        }
        else if(sortInfo->type == BUBBLE){
            i = 0;
            j = 0;
            connect(timer, &QTimer::timeout, this, &MainWindow::bubbleSortStep);
        }
        else if(sortInfo->type == SHELL){
            h = 1;
            int len = arr->getLen();
            // 计算h的值
            while(h < len/3)
                h = 3*h + 1;
            i = h;
            j = i;
            connect(timer, &QTimer::timeout,this,&MainWindow::shellSortStep);
        }
        else if(sortInfo->type == QUICK){
            i = 0;
            recordQuickSort();
            connect(timer,&QTimer::timeout, this, &MainWindow::quickSortStep);
        }
        startSorting();
        update();
    }
}


void MainWindow::on_resetBtn_clicked()
{
    if(!timer){
        arr->reset();
        bars->clear();
        scene->clear();
        if(record->getNum() > 0)
            record->clear();
        sorts->reSet();
        update();
    }
}

void MainWindow::startSorting()
{
    sorted = false;
    timer->start(500); // 间隔设置为500ms
}

void MainWindow::insertionSortStep()
{
    if(sorted || i >= bars->getNum()){
        timer->stop();
        timer = NULL;
        return;
    }

    // 计算一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;
    int startX = gap;

    // 记录要插入的bar
    int key = arr->getKth(i);
    //QGraphicsRectItem *keyBar = bars[i];
    QGraphicsRectItem *keyBar = bars->getKth(i)->item;
    int j = i - 1;

    // 找到要插入的位置j
    // 从后往前逐一比较（直接插入排序）
    // 与大于key的bar交换
    while(j >= 0 && arr->getKth(j) > key){
        //bars[j+1] = bars[j];
        //bars[j+1]->setRect(startX + (j+1)*width, 650 - bars[j+1]->rect().height(), width - 2*gap, bars[j+1]->rect().height());
        bars->setKth(bars->getKth(j)->item, j+1);
        QGraphicsRectItem *barJ1 = bars->getKth(j+1)->item;
        barJ1->setRect(startX + (j+1)*width, 650 - barJ1->rect().height(), width - 2*gap, barJ1->rect().height());
        arr->changeKth(arr->getKth(j), j+1);
        sorts->addTime();
        sorts->addTimeSwap();
        j--;
    }
    if(j >= 0)
        sorts->addTime();

    //bars[j+1] = keyBar;
    //bars[j+1]->setRect(startX + (j+1)*width,650-key*maxheight/maxValue, width-2*gap, key*maxheight/maxValue);
    // 将key放置在目标位置
    bars->setKth(keyBar, j+1);
    bars->getKth(j+1)->item->setRect(startX + (j+1)*width,650-key*maxheight/maxValue, width-2*gap, key*maxheight/maxValue);
    for(int k = j + 1; k <= i; k++)
        bars->getKth(k)->item->setBrush(Qt::green);
    arr->changeKth(key, j+1);

    i++;
    update();
    if(i >= bars->getNum())
        sorted = true;

}

void MainWindow::selectSortStep()
{
    if(sorted || i >= bars->getNum()){
        timer->stop();
        timer = NULL;
        return;
    }

    // 计算一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;
    int startX = gap;
    int len = arr->getLen();

    // 从第i个元素开始找到最小的元素
    int key = arr->getKth(i);
    int keyPos = i;
    for(int j = i+1; j < len; j++){
        sorts->addTime();
        if(arr->getKth(j) < key){
            key = arr->getKth(j);
            keyPos = j;
        }
    }

    //QGraphicsRectItem *target = bars[keyPos];
    // 将最小元素与i位置交换
    QGraphicsRectItem *target = bars->getKth(keyPos)->item;
    bars->getKth(i)->item->setRect(startX + i*width, 650-target->rect().height(),width-2*gap, target->rect().height());
    target->setRect(startX + keyPos*width, 650-arr->getKth(i) * maxheight / maxValue, width-2*gap, arr->getKth(i) * maxheight / maxValue);
    arr->swap(i,keyPos);
    sorts->addTimeSwap();

    bars->getKth(i)->item->setBrush(Qt::green);
    i++;
    update();
    if(i >= bars->getNum())
        sorted = true;
}

void MainWindow::binaryInsertionSortStep()
{
    if(sorted || i >= bars->getNum()){
        timer->stop();
        timer = NULL;
        return;
    }

    // 设置一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;
    int startX = gap;

    int key = arr->getKth(i);

    // 找到要插入的位置
    // 二分法查找（折半插入排序）
    int low = 0, height = i - 1;
    while(low <= height){
        int mid = (low + height) / 2;
        sorts->addTime();
        if(arr->getKth(mid) < key)
            low = mid + 1;
        else
            height = mid - 1;
    }

    // 将key交换到目标位置
    for(int j = i; j > low; j--){
        //QGraphicsRectItem *lastBar = bars[j-1];
        QGraphicsRectItem *lastBar = bars->getKth(j-1)->item;
        QGraphicsRectItem *barJ = bars->getKth(j)->item;
        //bars[j]->setRect(bars[j]->rect().x(),650-lastBar->rect().height(),lastBar->rect().width(),lastBar->rect().height());
        barJ->setRect(barJ->rect().x(),650-lastBar->rect().height(),lastBar->rect().width(),lastBar->rect().height());
        arr->changeKth(arr->getKth(j-1), j);
        sorts->addTimeSwap();
    }
    arr->changeKth(key,low);
    bars->getKth(low)->item->setRect(startX+low*width,650-key*maxheight/maxValue, width-2*gap, key*maxheight/maxValue);
    for(int k = low; k <= i; k++)
        bars->getKth(k)->item->setBrush(Qt::green);

    i++;
    update();
    if(i >= bars->getNum())
        sorted = true;
}

void MainWindow::bubbleSortStep()
{
    if(sorted || i >= bars->getNum()){
        timer->stop();
        timer = NULL;
        return;
    }

    // 设置一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;
    int len = arr->getLen();

    // 模拟双循环
    if(j < len - 1 - i){
        // 内循环
        sorts->addTime();
        // 交换二者
        if(arr->getKth(j) > arr->getKth(j+1)){
            int key = arr->getKth(j);
            arr->changeKth(arr->getKth(j+1), j);
            arr->changeKth(key, j+1);
            QGraphicsRectItem *barJ1 = bars->getKth(j+1)->item;
            QGraphicsRectItem *barJ = bars->getKth(j)->item;
            barJ->setRect(barJ->rect().x(),650-barJ1->rect().height(),width - 2*gap,barJ1->rect().height());
            barJ1->setRect(barJ1->rect().x(),650 - key*maxheight/maxValue,width-2*gap,key*maxheight/maxValue);
            sorts->addTimeSwap();
        }
        j++;
    }
    else{
        // 外循环
        bars->getKth(len-i-1)->item->setBrush(Qt::green);
        i++;
        j = 0;
    }

    update();
    if(i >= bars->getNum())
        sorted = true;
}

void MainWindow::shellSortStep()
{
    if(sorted || h < 1){
        timer->stop();
        timer = NULL;
        return;
    }

    // 设置一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;
    int len = arr->getLen();

    // 三重循环
    if(j >= h)
        sorts->addTime();
    if(j >= h && arr->getKth(j) < arr->getKth(j - h)){
        // 内循环
        // 交换二者
        arr->swap(j,j-h);
        QGraphicsRectItem *barJh = bars->getKth(j-h)->item;
        QGraphicsRectItem *barJ = bars->getKth(j)->item;
        barJ->setRect(barJ->rect().x(), 650-arr->getKth(j)*maxheight/maxValue, width-2*gap, arr->getKth(j)*maxheight/maxValue);
        barJh->setRect(barJh->rect().x(), 650-arr->getKth(j-h)*maxheight/maxValue, width-2*gap, arr->getKth(j-h)*maxheight/maxValue);
        j-=h;
        sorts->addTimeSwap();
    }
    else{
        i++;
        if(i < len){
            j = i;
        }
        else{
            // 外循环
            h = h/3;
            i = h;
            j = i;
        }
    }


    update();
    if(h < 1)
        sorted = true;
}

void MainWindow::quickSortStep()
{
    // 计算一系列数值（绘图用）
    int maxValue = arr->getMax();
    double width = 1230 / arr->getLen();
    int gap = width / 20;
    int maxheight = 640;

    // 按照record记录画长方形
    if(i < record->getNum()){
        int i_q = record->getKth(i), j_q = record->getKth(i+1);
        int key = arr->getKth(i_q);
        QGraphicsRectItem *barI = bars->getKth(i_q)->item;
        QGraphicsRectItem *barJ = bars->getKth(j_q)->item;
        barI->setRect(barI->rect().x(), 650-barJ->rect().height(), width-2*gap, barJ->rect().height());
        barJ->setRect(barJ->rect().x(),650-key*maxheight/maxValue, width-2*gap,key*maxheight/maxValue);
        arr->swap(i_q, j_q);
        sorts->addTimeSwap();
        update();
        i+=2;
    }
    else{
        timer->stop();
        timer = NULL;
    }
}

void MainWindow::quickSort(int low, int height)
{
    int mid;
    if(low < height){
        mid = part(low, height);
        quickSort(low, mid-1); // 排左边
        quickSort(mid+1,height); // 排右边
    }
}

void MainWindow::recordQuickSort()
{
    record->clear();
    arr_->copy(*arr);
    quickSort(0, arr_->getLen()-1);
}

int MainWindow::part(int low, int height)
{
    int i_q = low, j_q = height, pivot = arr_->getKth(low);
    while (i_q < j_q) {
        while (i_q < j_q && arr_->getKth(j_q) > pivot){
            sorts->addTime();
            j_q--; // 左移
        }
        if (i_q < j_q){
            sorts->addTime();
            record->addRecord(i_q);
            record->addRecord(j_q);
            arr_->swap(i_q++, j_q);
        }
        while (i_q < j_q && arr_->getKth(i_q) <= pivot){
            sorts->addTime();
            i_q++; // 右移
        }
        if (i_q < j_q){
            sorts->addTime();
            record->addRecord(i_q);
            record->addRecord(j_q);
            arr_->swap(i_q, j_q--);
        }
    }
    return i_q;
}

