#include "HornBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

HornBug::HornBug()
{
}


HornBug::~HornBug()
{
	SAFE_RELEASE(m_pPlayerLeftSencer);
	SAFE_RELEASE(m_pPlayerRightSencer);

}

bool HornBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
			return false;
	}

	Bug::SetAnimation("DB");
	m_pMesh->SetPivot(0.5f, 0.528f, 0.f);

	// �÷��̾� ã������ ����
	m_pPlayerLeftSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerLeftSencer->GetBody();
	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);


	m_pPlayerRightSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerRightSencer->GetBody();

	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);

	m_fMoveSpeed = 100.f;

	m_pPlayerLeftSencer->SetRelativePos(-300.f, 0.f, 0.f);
	m_pPlayerRightSencer->SetRelativePos(300.f, 0.f, 0.f);

	return true;
}

void HornBug::Begin()
{
	Bug::Begin();

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);
}

void HornBug::Update(float fTime)
{
	Bug::Update(fTime);

	// ���ư��� �������� �ƹ��͵� ���Ѵ�.
	if (false == m_bOnLand)
	{
		return;
	}

	// ����
	if (true == m_bDead)
	{
		m_pMesh->SetPivot(0.5f, 0.58f, 0.f);
		return;
	}






	// �ȴٰ� �Ǵ� ���ִٰ� �÷��̾ ����
	
	if ((BS_WALK == m_eState || BS_STAND == m_eState))
	{
		// ���� ���� �ִµ� ���ʿ� �ִ� ���
		if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			Dash(fTime);
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			return;
		}

		// ���� ���� �ִµ� �����ʿ� �ִ� ���

		// ������ ���� �ִµ� ���ʿ� �ִ� ���

		// ������ ���� �ִµ� �����ʿ� �ִ� ���
		else if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			Dash(fTime);
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			return;
		}
	}
	



	// �غ��� ������ �޸���
	if (BS_BWALK == m_eState && m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_DASH);
		m_pMovement->SetMoveSpeed(500.f);
		return;
	}

	// �뽬�ϰ� �ִٰ� ���ư���
	if (BS_DASH == m_eState)
	{
		m_fDashTime += fTime;

		SetCurrentState(BS_DASH);

		if (m_fDashTime >= m_fDashTotalTime)
		{
			m_fDashTime = 0.f;
			SetCurrentState(BS_STAND);
			m_fWalkTime = 0.f;
			return;
		}
	}

	// �ȱ� ���ư���
	if (BS_WALK == m_eState)
	{
		m_fWalkTime += fTime;
		SetCurrentState(BS_WALK);
		m_pMovement->SetMoveSpeed(m_fMoveSpeed);

		// �ȿ����̱�
		if (m_fWalkTime >= m_fWalkTotalTime)
		{
			SetCurrentState(BS_STAND);
			m_pMovement->SetMoveSpeed(0.f);
			m_fWalkTime = 0.f;
			return;
		}

		return;
	}

	// ���ִٰ� ���ư���
	if (BS_STAND == m_eState)
	{
		m_fStandTime += fTime;

		SetCurrentState(BS_STAND);
		// �ȿ����̱�
		m_pMovement->SetMoveSpeed(0.f);

		if (m_fStandTime >= m_fStandTotalTime)
		{
			// �ٽ� �����̱�
			m_fStandTime = 0.f;
			SetCurrentState(BS_WALK);
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);
			return;
		}
	}





}

void HornBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void HornBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void HornBug::Reverse()
{
}

void HornBug::CheckFront()
{
	Bug::CheckFront();
}

void HornBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void HornBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void HornBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}


void HornBug::Dash(float fTime)
{
	SetCurrentState(BS_BWALK);

	m_pMovement->SetMoveSpeed(0.f);



}

void HornBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}


void HornBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	Bug::OnBlock(pSrc, pDest, fTime);
}

void HornBug::ClearState()
{

}