#include "RunTileManager.h"


RunTileManager::RunTileManager(void)
{
	_width = 0;
	_height = 0;
	i = 0;
	howlongfall = 0;
	h_type = 0;

}


RunTileManager::~RunTileManager(void)
{
}

void RunTileManager::Init(LPWSTR _path)
{
	m_HuddleTex[0] = new CTexture;
	m_HuddleTex[1] = new CTexture;
	m_HuddleTex[2] = new CTexture;
	m_HuddleTex[0]->LoadTexture(L"Image\\Hurdle\\fire.png");
	m_HuddleTex[1]->LoadTexture(L"Image\\Hurdle\\notice.png");
	m_HuddleTex[2]->LoadTexture(L"Image\\Hurdle\\turret.png");

	Hurdle = new CTile;
	Hurdle->init( m_HuddleTex[0]->GetTexture() , 0 , -3000 , 0 , 0 ) ;
	for(i = 0 ; i<AMAX ; ++i)
	{
		sector1[i] = new CTile;
		sector2[i] = new CTile;
	}

	m_fallTex = new CTexture;
	m_fallTex->LoadTexture(L"Image\\Tile\\fall.png");

	for( i = 0 ; i<3 ; ++i)
	{
		fall[i] = new CTile;
		fall[i]->init( m_fallTex->GetTexture() , 0 , -3000 , 0 , 0 ) ;
	}
	m_tileTex = new CTexture;

	m_tileTex->LoadTexture( _path );
	_width = m_tileTex->GetTexture()->_imageifo.Width;
	_height = m_tileTex->GetTexture()->_imageifo.Height;
	int pos = Core()->GetScreenHeight() - _height;

	for(i = 0 ; i<AMAX ; ++i)
	{
		sector1[i]->init( m_tileTex->GetTexture(), i*_width ,pos , 0 , 0 );
		sector2[i]->init( m_tileTex->GetTexture(), (i+AMAX)*_width ,pos , 0 , 0 );
	}
	//cout<<sector2[9]->GetConstPosition().x<<endl;
}

void RunTileManager::Uninit()
{	
	for(i = 0 ; i<AMAX ; ++i)
	{
		if( sector1[i] != NULL )
		{
			delete sector1[i];
			sector1[i] = NULL;	
		}
	}
	for(i = 0 ; i<AMAX ; ++i)
	{
		if( sector2[i] != NULL )
		{
			delete sector2[i];
			sector2[i] = NULL;	
		}
	}
	if ( m_tileTex != NULL )
	{
		m_tileTex->ReleaseTexture();
		delete m_tileTex;
		m_tileTex = NULL;
	}
	if ( m_fallTex != NULL )
	{
		m_fallTex->ReleaseTexture();
		delete m_fallTex;
		m_fallTex = NULL;
	}
	



	for( i = 0 ; i<3 ; ++i)
	{
		if( m_HuddleTex[i] != NULL )
		{
			m_HuddleTex[i]->ReleaseTexture();
			delete m_HuddleTex[i];
			m_HuddleTex[i] = NULL;
		}
		if( fall[i] != NULL)
		{
			delete fall[i];
			fall[i] = NULL;
		}
		
	}
}

void RunTileManager::Render()
{
	for(i = 0 ; i<AMAX ; ++i)
	{
		sector1[i]->Render();
		sector2[i]->Render();
	}
	for( i = 0 ; i<3 ; ++i)
	{
		fall[i]->Render();
	}
	Hurdle->Render();
}

void RunTileManager::Process()
{
	for(i = 0 ; i<AMAX ; ++i)
	{
		sector1[i]->ConstMove(-10 , 0 );
		sector2[i]->ConstMove(-10 , 0 );
		sector1[i]->Process();
		sector2[i]->Process();
	}
	for( i = 0 ; i<3 ; ++i)
	{
		fall[i]->ConstMove( -10 , 0 );
		fall[i]->Process();
	}
	Hurdle->Process();
	Hurdle->ConstMove( - 10 , 0 );
//	cout<<Hurdle->GetConstPosition().x<<endl;
	if( sector1[AMAX-1]->GetConstPosition().x + _width < 0 )
	{
		SectorSwap();
		SectorReset();
	}
}

void RunTileManager::SectorSwap()
{
	CTile* temp ;	

	for(i = 0 ; i<AMAX ; ++i)
	{
		temp = sector1[i];
		sector1[i] = sector2[i];
		sector2[i] = temp;
	}
}

void RunTileManager::SectorReset()
{
	int temp = sector1[AMAX-1]->GetConstPosition().x + _width;
	int pos = Core()->GetScreenHeight() - _height;
	int pos2 =  Core()->GetScreenHeight() - m_fallTex->GetTexture()->_imageifo.Height;
	
	srand( Core()->MyGetTickCount() );
	howlongfall = rand() % 3 ; 
	h_type = rand() % 3;

	if( fall[0]->GetConstPosition().x > -100 && fall[0]->GetConstPosition().x < Core()->GetScreenWidth() )
	{	
		isfallused = true;
	}
	else
	{	
		isfallused = false;
	}
	if( Hurdle->GetConstPosition().x > -100  )
	{
		ishurdle = true;
	}
	else
	{
		ishurdle = false;
	}

	for(i = 0 ; i<AMAX ; ++i)
	{	
		if( i < howlongfall && i < 3 && !isfallused )
			fall[i]->SetConstPosition( temp+(i*_width) , pos2 );
		else
			sector2[i]->SetConstPosition( temp+(i*_width) , pos );
	}

	if( !ishurdle)
	{
		Hurdle->SetTex( m_HuddleTex[h_type]->GetTexture() );
		Hurdle->SetConstPosition( sector2[AMAX-4]->GetConstPosition().x, pos - Hurdle->Getheigth()) ;
	}
//	cout<<Hurdle->GetConstPosition().x<<endl;
}

D3DXVECTOR3 RunTileManager::GetFallPosition()
{
	return fall[i]->GetConstPosition();
}

D3DXVECTOR3 RunTileManager::GetHurdlePosition()
{
	return Hurdle->GetConstPosition();
}

