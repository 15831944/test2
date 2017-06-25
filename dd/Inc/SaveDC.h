#ifndef __SAVEDC_H__
#define __SAVEDC_H__

class CSaveDC
{
public:
	CSaveDC(CDC &dc)
	{
		m_sdc = &dc;
		m_saved = dc.SaveDC();
	}

	CSaveDC(CDC* dc)
	{
		m_sdc = dc;
		m_saved = dc->SaveDC();
	}
	
	virtual ~CSaveDC()
	{
		m_sdc->RestoreDC(m_saved);
	}
	
protected:
	CDC* 	m_sdc;
	int 	m_saved;
};

#endif