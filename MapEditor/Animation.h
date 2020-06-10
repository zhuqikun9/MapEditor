#pragma once
#include "texture.h"
  

//动画类
class CAnimation :
	public CTexture
{
public:
	CAnimation(void);
	~CAnimation(void);
	//初始化，需要指定每行每列帧数,以及播放速度
	virtual	 void		Create(LPCTSTR Filename, int FramesPerRow, int FramesPerCol,float FPS);
	//绘画
	virtual  void		Draw(CDC* pDC,int xDest,int yDest,int nDestWidth=0,int nDestHeight=0);


	//播放一段帧序列  ，起始编号，序列帧长度
    void		SetFramesQueue(int StartNum,int length) ;
	//上一帧  
    void		PrevFrame(float fDeltaTime) ;   
    //下一帧  
    void		NextFrame(float fDeltaTime);    
	  
    //设定播放速度
	void		SetSpeed(float FPS) { m_fSpeed=1.0f/FPS; }  
	//将投影中心设置为图片的底部正中间位置
	void		SetProjCenter(){ SetHotSpot(m_FrameWidth/2,m_FrameHeight); }
	//设置是否可见 
	void		SetVisible(bool visible){ m_bVisible=visible;}  
	//判断当前一段动画是否播放结束
	bool		IsFrameEnd(){ return m_nCurFrame==(m_nStartFrame+m_TotalFrames-1); }
	//设定当前帧编号
	void		SetCurFrame(int index){   m_nCurFrame = index ;   }
	//获取速度（fps）帧率
	float		GetSpeed() const { return 1.0f/m_fSpeed; }
	//获取当前帧序号
	int			GetCurFrame() const { return m_nCurFrame; }
	int			GetFrameWidth(){ return m_FrameWidth; }
	int			GetFrameHeight(){return m_FrameHeight; }
	//获取起始帧编号
	int			GetStartFrame() const { return m_nStartFrame; }
    //获取一段动画序列长度  
    int			GetFramesCount() {      return m_TotalFrames ;  }                  
    //获取每行动画序列长度，图片切割后  
	int			GetFramesPerRow() {return m_FramesPerRow;}  
	int			GetFramesPerCol() {return m_FramesPerCol;}  
	//设置当前帧,根据帧编号计算出该帧编号对应的图片源矩形位置，
    void		SetFrameRect(int index) ;  
	                                      
public:

	CRect		m_SrcRect;		//源矩形(图片)
	CRect		m_DestRect;		//目的矩形（屏幕）
protected:
	//播放一帧所需时间
	float		m_fSpeed;
	float		m_fSinceLastFrame;

	int			m_nStartFrame;	//起始帧编号
	int			m_nCurFrame ; //当前帧编号 从第1帧开始算  
	int			m_TotalFrames ; //一段帧动画个数，要播放多少帧 

    int			m_FrameWidth; //每帧宽度和高度
    int			m_FrameHeight;
    int			m_FramesPerRow ; //图片每1行动画帧数          
    int			m_FramesPerCol ; //图片每1列动画帧数
	bool		m_bVisible;
};

