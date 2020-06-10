#include "StdAfx.h"
#include "Animation.h"


CAnimation::CAnimation(void)
{

	ZeroMemory(&m_SrcRect,sizeof(m_SrcRect));
	m_FrameWidth=0;
	m_FrameHeight=0;
	m_fSinceLastFrame=-1.0f;
	m_fSpeed=0;
	m_nCurFrame=0;//当前帧序号
	m_nStartFrame=0;
	m_TotalFrames=0;
	m_SrcRect.SetRectEmpty();		//源矩形(图片)
	m_DestRect.SetRectEmpty();
	m_bVisible = true;
}


CAnimation::~CAnimation(void)
{
}


void CAnimation::Create(LPCTSTR Filename, int FramesPerRow, int FramesPerCol,float FPS)
{
	CTexture::Create(Filename);
	m_FramesPerRow=FramesPerRow;
	m_FramesPerCol=FramesPerCol;

	m_FrameWidth=GetWidth()/m_FramesPerRow;
	m_FrameHeight=GetHeight()/m_FramesPerCol;
	//设置速度
	SetSpeed(FPS);
	//设置帧序列  

	SetFrameRect(m_nCurFrame);
}

//设置帧序列  
void CAnimation::SetFramesQueue(int StartNum,int length)   
{  
    //赋值动画序列长度  
	m_nStartFrame = StartNum;
    m_TotalFrames = length ;   
}  



//倒退一帧  
void CAnimation::PrevFrame(float fDeltaTime)  
{  
	//重置每两个动画帧时间差
	if(m_fSinceLastFrame == -1.0f)
		m_fSinceLastFrame=0.0f;
	else
		m_fSinceLastFrame += fDeltaTime;//累加时间片段
	//当时间差大于播放一帧所需时间时，才进行循环
	while(m_fSinceLastFrame >= m_fSpeed)
	{	
		m_fSinceLastFrame -= m_fSpeed;
		if( m_nCurFrame <= m_nStartFrame||m_nCurFrame > (m_nStartFrame+m_TotalFrames-1) )  
		{  
		    m_nCurFrame = m_nStartFrame+m_TotalFrames-1 ;  
		}     
		else  
		{  
			m_nCurFrame-- ;  
		}  
	
	}
	SetFrameRect(m_nCurFrame);

}  
//播放下一帧  
void CAnimation::NextFrame(float fDeltaTime)   
{  
	//重置每两个动画帧时间差
	if(m_fSinceLastFrame == -1.0f)
		m_fSinceLastFrame=0.0f;
	else
		m_fSinceLastFrame += fDeltaTime;//累加时间片段
	//当时间差大于播放一帧所需时间时，才进行循环
	while(m_fSinceLastFrame >= m_fSpeed)
	{	
		m_fSinceLastFrame -= m_fSpeed;
		//如果播放结束，回到起始帧编号
		if(m_nCurFrame<m_nStartFrame||m_nCurFrame >= (m_nStartFrame+m_TotalFrames-1) )  
		{  
			m_nCurFrame = m_nStartFrame ;  
		}  
		else  
		{  //当前帧编号
			m_nCurFrame++ ;  	
		}  
	}  
	//切换帧
	SetFrameRect(m_nCurFrame);
}  

//绘制精灵  
void CAnimation::Draw(CDC* pDC,int xDest,int yDest,int nDestWidth,int nDestHeight)   
{  
    if(!m_bVisible)  
		return ;
	if(nDestWidth ==0)
		nDestWidth=m_SrcRect.Width();
	if(nDestHeight==0)
		nDestHeight=m_SrcRect.Height();
	return CTexture::Draw(pDC,xDest,yDest,nDestWidth,nDestHeight,m_SrcRect.left,m_SrcRect.top,m_SrcRect.Width(),m_SrcRect.Height());
		
}  

//根据当前帧编号，计算出对应的源图片矩形位置
void CAnimation::SetFrameRect(int index)
{
	//源矩形Y坐标 ， m_nCurFrame当前帧编号，m_FramesPerRow每行帧数
    int Y = m_nCurFrame / m_FramesPerRow;  
    //源矩形X坐标   
    int X = m_nCurFrame - Y * m_FramesPerRow;     

	m_SrcRect.left	= X*m_FrameWidth;
    m_SrcRect.top	= Y*m_FrameHeight;
    m_SrcRect.right	= m_SrcRect.left + m_FrameWidth;
    m_SrcRect.bottom	= m_SrcRect.top + m_FrameHeight;
	
}

//void CAnimation::MoveInMap(int dx,int dy)
//{
//	m_PosX+=dx;
//	m_PosY+=dy;
//}
////投放到地图上（x,y）位置
//void CAnimation::MoveToMap(int x,int y)
//{
//	m_PosX = x;
//	m_PosY = y;
//}