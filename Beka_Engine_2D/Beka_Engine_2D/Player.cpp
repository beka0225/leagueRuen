#include "Player.h"


CPlayer::CPlayer(void)
{
	isJump = false;
}


CPlayer::~CPlayer(void)
{

}
void CPlayer::Uninit()
{
	m_Run->RemoveImage();
	m_Run->UnInit();
	delete m_Run;
	m_Run = NULL;
}

void CPlayer::SetPositon(float x, float y)
{
	(*m_Current)->Warp( x, y ,0.f);
	m_position.x = x;
	m_position.y = y;
}

void CPlayer::Init( int Charactertype = 0 )
{
	m_Run =  new CUIObject;
//	m_Jump = new CUIObject;
//	m_DJump = new CUIObject;
//	m_Beshot = new CUIObject;
//	m_Fall = new CUIObject;
//	m_HFall = new CUIObject;
	m_Current = &m_Run;
	switch( Charactertype )
	{
	case 0:
		m_Run->Init(L"Image\\Player\\izreal_stand.png");
		_width = m_Run->GetWidth();
		_height = m_Run->GetHeight();
//		m_Run->Init();
//		m_Jump->Init();
//		m_DJump->Init();
//		m_Beshot->Init();
//		m_Fall->Init();
//		m_HFall->Init();
		break;
	}
}

void CPlayer::Render()
{
	(*m_Current)->Render();
}

void CPlayer::Process()
{
	switch( m_State )
	{
	case RUN:
		break;
	case JUMP:
		break;
	case DOUBLEJUMP:
		break;
	case BESHOT:
		break;
	case FALL:
		break;
	case HIGHFALL:
		break;	
	}
	if( isJump )
	{
		Jump();
	}
	(*m_Current)->Process();
}



void CPlayer::SetState(int val)
{
	m_State = val;
	switch( m_State )
	{
	case RUN:
		m_Current = &m_Run;
		break;
	case JUMP:
//		m_Current = &m_Jump;
		break;
	case DOUBLEJUMP:
//		m_Current = &m_DJump;
		break;
	case BESHOT:
	//	m_Current = &m_Beshot;
		break;
	case FALL:
	//	m_Current = &m_Fall;
		break;
	case HIGHFALL:
	//	m_Current = &m_HFall;
		break;	
	}
}

void CPlayer::Jump()
{

	acc -= 0.2f ;
	int temp = m_position.y - 10 * acc ;
	m_position.y = temp;

	(*m_Current)->Warp( m_position.x , m_position.y );
	cout<<m_position.y<<endl;
	
	if( m_position.y >= startpos )
	{
		m_position.y = startpos;
		(*m_Current)->Warp( m_position.x , m_position.y );
		isJump = false;
	}

}

void CPlayer::JumpStart()
{
	if( isJump && isDjump) // double jump
	{
		isDjump;
		acc = 3.0f;
		isDjump = false;
	}
	else if( !isJump && !isJump)
	{
		isDjump = true;
		isJump = true;
		acc = 3.0f;
	}
}