#include <Windows.h>
#include <mmsystem.h>

#include "Direct3D.h"
#include "Core.h"

#include "DirectInput.h"
#include "DirectSound.h"

#include "SceneHeader.h"
#include "SceneManager.h"
#include "TileManager.h"
//#include "Setting.h"


CStartScene::CStartScene(void)
{
	BG1 = new CBackGround;
	BG2 = new CBackGround;
	BG1->Init( L"Image\\BackGround\\BG.png" , 0 , 0 , 1.f );
	BG2->Init( L"Image\\BackGround\\BackGround_Close.png", 0 ,0, 0.5);
}


CStartScene::~CStartScene(void)
{

}

bool CStartScene::Initialize()
{
	temp.Init( "Data\\game_option.ini" ) ;
	temp.SetSection( "Option" );
	temp.SetKey("MouseSense");
	temp.Write( 56 );

	m_player = new CPlayer;
	m_player->Init( 0 );
	
	m_tileManager = new RunTileManager;
	m_tileManager->Init( L"Image\\Tile\\tile_league.png" );
	m_player->SetPositon(200, Core()->GetScreenHeight() - m_player->GetHeight() - m_tileManager->GetHeight() );
	m_player->SetStartPosition( Core()->GetScreenHeight() - m_player->GetHeight() - m_tileManager->GetHeight() );
	cout<<temp.Read()<<endl;

	return true;
}

void CStartScene::UnInitialize()
{
	BG1->UnInit();
	BG2->UnInit();
	m_tileManager->Uninit();
	m_player->Uninit();

}

bool CStartScene::TextureInitialize()
{
	return true;
}

void CStartScene::TextureUnInitialize()
{

}

void CStartScene::PrepareInput()
{
	if( DirectInput()->KeyPress(DIK_RIGHT) )
	{
		Camera()->Move( MOVE_VAL );
	}
		if( DirectInput()->KeyPress(DIK_LEFT) )
	{
		Camera()->Move( -MOVE_VAL );
	}

	if ( DirectInput()->KeyDown(DIK_ESCAPE ) )
	{
		PostQuitMessage(0);
	}
	if(DirectInput()->KeyDown(DIK_SPACE))
	{
		m_player->JumpStart();
	}

}

void CStartScene::Process()
{
	if( m_tileManager->GetFallPosition().x < m_player->GetPosition()->x &&  m_tileManager->GetFallPosition().x + m_tileManager->GetWidth() *m_tileManager->GetHowlongfall() && m_tileManager->GetHowlongfall() != 0  )
	{
		cout<<"fall"<<endl;
	}
	m_player->Process();
	BG1->Process();
	BG2->Process();
	m_tileManager->Process();
	return;

}

void CStartScene::Render()
{
	BG1->Render();
	BG2->Render();
	m_tileManager->Render();
	m_player->Render();
	return;

}