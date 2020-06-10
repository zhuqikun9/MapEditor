#pragma once
//图片类，对CImage的简单封装，用于图片的加载和绘制

class CTexture
{
public:
	CTexture();
	~CTexture(void);
	CTexture& operator=(const CTexture &texture)
	{	
		if(this==&texture) 
			return *this; Destroy();
													
		this->Create (texture.m_Image);													
		this->m_FileName=texture.m_FileName;																
		this->m_SrcWidth = texture.m_SrcWidth;																
		this->m_SrcHeight = texture.m_SrcHeight;		
		this->m_HotX = texture.m_HotX;
		this->m_HotY = texture.m_HotY;
		return *this;		
	}
	//加载一个图图片，默认以图片左上角颜色为透明色	
	virtual  void	Create(LPCTSTR FileName);
	//复制一个图片，默认以图片左上角颜色为透明色
	virtual  void	Create(const CImage& srcImage);
	//简单画图
	virtual  void	Draw(CDC* pDC,int xDest,int yDest,BYTE alpha);
	//自适应绘制整个图片
	virtual  void	Draw(CDC* pDC,int xDest,int yDest,int nDestWidth,int nDestHeight);
	//自适应绘制图片，带透明通道
	virtual  void	Draw(CDC* pDC,int xDest,int yDest,int nDestWidth,int nDestHeight,BYTE alpha);
	//绘制源图片的一部分
	virtual  void	Draw(CDC* pDC,int xDest,int yDest,int nDestWidth,int nDestHeight,
					int xSrc,int ySrc,int nSrcWidth,int nSrcHeight);
	//设置绘制基准点坐标
	void	SetHotSpot(int x,int y){ m_HotX = x;	m_HotY = y;}
	CPoint	GetHotSpot(){	return CPoint(m_HotX,m_HotY); }
	//设置图片过滤色，
	void	SetColorKey(COLORREF alpha){ m_Image.SetTransparentColor(alpha);}
	//返回CImage对象
	CImage&	GetImage(){	return m_Image; }
	int		GetWidth(){	return m_SrcWidth;	}
	int		GetHeight(){ return m_SrcHeight; }
	CString GetFileName(){ return m_FileName; }
	//判断是否为空
	bool	IsEmpty(){return m_Image.IsNull(); }
	//销毁图片
	void	Destroy(){ m_Image.Destroy(); }
public:
	//图片宽度
	int		m_SrcWidth;
	//图片高度
	int		m_SrcHeight;
	//图片原点坐标
	int		m_HotX;
	int		m_HotY;
	//文件名
	CString		m_FileName;
	//存放图片
	CImage		m_Image;

};

