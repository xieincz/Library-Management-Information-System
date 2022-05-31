#include "captchabox/captchabox.h"
#include "time.h"
#include <QtGlobal>
#include <QLabel>

CaptchaBox::CaptchaBox(QWidget *parent)
    : QWidget(parent)
{
    srand(time(0));//产生随机数种子
    initCharset();
    initColorset();
    initDefaultFont();
    generateCaptcha();
    this->setStyleSheet("background-color: red;");
}

CaptchaBox::~CaptchaBox()
{
}

void CaptchaBox::initCharset()
{
    //初始化英文字符(数字和大小写字母)
    QString tempStringEn(tr("0123456789abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    for(int i=0;i<tempStringEn.size();i++)
    {
        charSetEn.append(tempStringEn.mid(i,1));
    }
    //初始化中文字符集(随便摘了段歌词)
    QString tmpStringCh(tr("昨夜同门云集推杯又换盏今朝茶凉酒寒豪言成笑谈半生累尽徒然碑文完美有谁看"
                      "隐居山水之间誓与浮名散湖畔青石板上一把油纸伞旅人停步折花淋湿了绸缎"
                      "满树玉瓣多傲然江南烟雨却痴缠花飞雨追一如尘缘理还乱落花雨你飘摇的美丽"
                      "花香氤把往日情勾起我愿意化浮萍躺湖心只陪你泛岁月的涟漪古木檀香小筑经文诵得缓"
                      "锦服华裳一炬粗袖如心宽林中抚琴曲委婉群山听懂我悲欢泪如雨落才知过往剪不断"
                      "落花雨你飘摇在天地晚风急吹皱芳华太无情我愿意化流沙躺湖堤只陪你恭候春夏的轮替"));
    for(int i =0;i<tmpStringCh.size();i++)
    {
        charSetCh.append(tmpStringCh.mid(i,1));
    }
}

void CaptchaBox::initColorset()
{
    //使用QT的枚举值初始化颜色集合 挑取比较深的颜色，浅色人眼不易识别
    colorSet<<QColor(Qt::black)<<QColor(Qt::red)<<QColor(Qt::darkRed)<<QColor(Qt::darkGreen)
           <<QColor(Qt::blue)<<QColor(Qt::darkBlue)<<QColor(Qt::darkCyan)<<QColor(Qt::magenta)
          <<QColor(Qt::darkMagenta)<<QColor(Qt::darkYellow);
}

void CaptchaBox::initDefaultFont()
{
    QFont defaultFont;//默认字体
    defaultFont.setFamily(tr(FONTFAMILY));
    defaultFont.setPointSize(FONTSIZE);
    defaultFont.setBold(true);//设置字体加粗
    this->setFont(defaultFont);
}

void CaptchaBox::generateCaptcha(int count)
{
    captchaChars.clear();
    if(rand()%2)//随机生成数字字母序列
    {
        int num = charSetEn.size();//获取字符集的大小
        for(int i=0;i<count;i++)
        {
            captchaChars.append(charSetEn.at(rand()%num));
        }
    }
    else//随机生成中文序列
    {
        int num = charSetCh.size();
        for(int i=0;i<count/2;i++)//中文个数是字母的一半
        {
            captchaChars.append(charSetCh.at(rand()%num));
        }
    }
    /* 根据验证码的字符和所设字体，确定整个验证码区域的高度和宽度。
     * 整个区域的大小会略大于验证码字符实际的大小。
     * 注：因为字符的宽度除了与字体有关系外,可能还与字符本身有关系。为了避免不同的
     * 验证码产生不同的宽度导致整个部件大小变化，这里以一个固定的英文字符(W,基本不上
     * 是所有英文字符中最宽的)求宽
     */
    boxHeight = this->fontMetrics().height()+SIZEINCREMENT;
    boxWidth = this->fontMetrics().horizontalAdvance("W")*count+SIZEINCREMENT;
    this->setFixedSize(boxWidth,boxHeight);//设置区域大小
}

void CaptchaBox::drawDisturb(QPainter &painter)
{
    int num = colorSet.size();//获取颜色集
    switch(rand()%3)
    {
    case 0: //四条水平方向随机干扰线
        painter.setPen(QPen(QBrush(QColor(colorSet.at(rand()%num))),1));
        painter.drawLine(0,rand()%boxHeight,boxWidth,rand()%boxHeight);
        painter.drawLine(0,rand()%boxHeight,boxWidth,rand()%boxHeight);
        painter.drawLine(0,rand()%boxHeight,boxWidth,rand()%boxHeight);
        painter.drawLine(0,rand()%boxHeight,boxWidth,rand()%boxHeight);
        break;
    case 1: //绘制干扰点
        for(int i=0;i<150;i++)
        {
            painter.setPen(QPen(QBrush(QColor(colorSet.at(rand()%num))),1));
            painter.drawPoint(rand()%boxWidth,rand()%boxHeight);
        }
        break;
    case 2: //水平加垂直干扰线
        painter.setPen(QPen(QBrush(QColor(colorSet.at(rand()%num))),1));
        painter.drawLine(0,boxHeight/5,boxWidth,boxHeight/5);
        painter.drawLine(0,boxHeight/5*2,boxWidth,boxHeight/5*2);
        painter.drawLine(0,boxHeight/5*3,boxWidth,boxHeight/5*3);
        painter.drawLine(0,boxHeight/5*4,boxWidth,boxHeight/5*4);
        painter.drawLine(boxWidth/6,0,boxWidth/6,boxHeight);
        painter.drawLine(boxWidth/6*2,0,boxWidth/6*2,boxHeight);
        painter.drawLine(boxWidth/6*3,0,boxWidth/6*3,boxHeight);
        painter.drawLine(boxWidth/6*4,0,boxWidth/6*4,boxHeight);
        painter.drawLine(boxWidth/6*5,0,boxWidth/6*5,boxHeight);
        break;
    default :break;
    }
}

void CaptchaBox::rotateAngle(QPainter &painter)
{
    //随机顺时针旋转随机角度
    if(rand()%2)
    {
        painter.rotate(rand()%ROTATEANGLE);
    }
    //随机逆时针旋转随机角度
    else
    {
        painter.rotate(-rand()%ROTATEANGLE);
    }
}

void CaptchaBox::scaleSize(QPainter &painter)
{
    //这里将放缩范围设置为0.9-1.1,scale
    double xSize = (rand()%3+9)/10.0;
    double ySize = (rand()%3+9)/10.0;
    painter.scale(xSize,ySize);
}

void CaptchaBox::shearForm(QPainter &painter)
{
    //扭曲的效果相似旋转和缩放组合，体现一种立体感，可以单独用
    //范围-0.3-0.3
    double xShear = rand()%4/10.0;
    double yShear = rand()%4/10.0;
    if(rand()%2)
    {
        xShear = -xShear;
    }
    if(rand()%2)
    {
        yShear = -yShear;
    }
    painter.shear(xShear,yShear);
}

void CaptchaBox::drawCaptcha(QPainter &painter)
{
    int num = colorSet.size();//获取颜色集的大小
    //根据验证码部件的大小均分每个字符所占空间,增量大小分配给部件的左右留白
    int charWidth = (boxWidth-SIZEINCREMENT)/captchaChars.size();
    drawDisturb(painter);//先绘制干扰元素
    for(int i=0;i<captchaChars.size();i++)
    {
        painter.setPen(QColor(colorSet.at(rand()%num)));//设置画笔为随机颜色
        //保存当前painter的状态，主要是坐标系状态，因为下面要使用平移旋转等操作改变坐标系
        painter.save();
        /* 因为rotate默认以坐标原点旋转，所以通过平移改变原点，以各文本原点旋转
         * 这里为了保证实际字符居中在各自的空间，需要求出字符左右留白的长度，同时将增量
         * 大小分给整个部件的左右留白
         */
        int charSpace = (charWidth-this->fontMetrics().horizontalAdvance(captchaChars.at(i)))/2;
        charSpace += SIZEINCREMENT/2;
        painter.translate(i*charWidth+charSpace,0);
        if(rand()%2)
        {
            //通过旋转放缩变形
            rotateAngle(painter);
            scaleSize(painter);
        }
        else
        {
            shearForm(painter);//直接对文本扭曲变形
        }
        /* 前两个参数指定画文本的起始位置，以文本左下角为起始点
         * 平移变换起始点的横坐标实际是i*charWidth+charSpace
         */
        painter.drawText(0,boxHeight-SIZEINCREMENT,captchaChars.at(i));
        painter.restore();//恢复之前的状态
    }
}

bool CaptchaBox::checkCaptcha(QString text)
{
    QString captchaString = captchaChars.join("");
    if(text.compare(captchaString,Qt::CaseInsensitive)==0)//不区分大小写
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CaptchaBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//painter会自动沿用绘图设备(this)的字体
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    QRect rect(QPoint(0,0),this->size());
    painter.drawRect(rect);//验证码整体背景设置白色

    drawCaptcha(painter);
    QWidget::paintEvent(event);
}

void CaptchaBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        generateCaptcha();//生成新的验证码
        update();//重新绘制
        QWidget::mousePressEvent(event);//执行重写前的鼠标按下的处理操作
    }
    QWidget::mousePressEvent(event);
}

