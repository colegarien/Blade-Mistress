//-----------------------------------------------------------------------------
// File: PointSprites.cpp
//-----------------------------------------------------------------------------
#define STRICT
#include <math.h>
#include <stdio.h>
#include <D3DX8.h>
//#include "D3DApp.h"
#include ".\puma\D3DFont.h"
#include ".\puma\D3DUtil.h"
#include ".\puma\DXUtil.h"
//#include "resource.h"

#include "pointsprites.h"




// Helper function to stuff a FLOAT into a DWORD argument
inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }





D3DXCOLOR g_clrColor[NUM_COLORS] =
{
    D3DXCOLOR( 1.0f,   1.0f,   1.0f,   1.0f ),
    D3DXCOLOR( 1.0f,   0.5f,   0.5f,   1.0f ),
    D3DXCOLOR( 0.5f,   1.0f,   0.5f,   1.0f ),
    D3DXCOLOR( 0.125f, 0.5f,   1.0f,   1.0f )
};


DWORD g_clrColorFade[NUM_COLORS] =
{
    D3DXCOLOR( 0.0f,   0.0f,   0.0f,   1.0f ),
//    D3DXCOLOR( 1.0f,   0.25f,   0.25f,   1.0f ),
    D3DXCOLOR( 1.0f,   0.25f,   0.25f,   1.0f ),
    D3DXCOLOR( 0.25f,  0.75f,   0.25f,   1.0f ),
    D3DXCOLOR( 0.125f, 0.25f,   0.75f,   1.0f )
};

/*
class CMyD3DApplication : public CD3DApplication
{
    CD3DFont*          m_pFont;
    CD3DFont*          m_pFontSmall;

    // Ground stuff
    LPDIRECT3DTEXTURE8 m_pGroundTexture;
    D3DXPLANE          m_planeGround;

    LPDIRECT3DVERTEXBUFFER8 m_pGroundVB;
    LPDIRECT3DINDEXBUFFER8  m_pGroundIB;
    DWORD              m_dwNumGroundIndices;
    DWORD              m_dwNumGroundVertices;

    // Particle stuff
    LPDIRECT3DTEXTURE8 m_pParticleTexture;
    CParticleSystem*   m_pParticleSystem;
    DWORD              m_dwNumParticlesToEmit;
    DWORD              m_dwParticleColor;
    BOOL               m_bAnimateEmitter;

    BYTE               m_bKey[256];
    BOOL               m_bDrawReflection;
    BOOL               m_bCanDoAlphaBlend;
    BOOL               m_bDrawHelp;

    // Variables for determining view position
    D3DXVECTOR3        m_vPosition;
    D3DXVECTOR3        m_vVelocity;
    FLOAT              m_fYaw;
    FLOAT              m_fYawVelocity;
    FLOAT              m_fPitch;
    FLOAT              m_fPitchVelocity;
    D3DXMATRIX         m_matView;
    D3DXMATRIX         m_matOrientation;

    HRESULT ConfirmDevice( D3DCAPS8*, DWORD, D3DFORMAT );

protected:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();
    VOID    UpdateCamera();

public:
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    CMyD3DApplication();
};
*/



/*
CMyD3DApplication::CMyD3DApplication()
{
    m_strWindowTitle    = _T("PointSprites: Using particle effects");
    m_bUseDepthBuffer   = TRUE;

    m_pFont                = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall           = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    m_pParticleSystem      = new CParticleSystem( 512, 2048, 0.03f );
    m_pParticleTexture     = NULL;
    m_dwNumParticlesToEmit = 10;
    m_bAnimateEmitter      = FALSE;
    m_dwParticleColor      = COLOR_WHITE;

    m_pGroundTexture       = NULL;
    m_dwNumGroundVertices  = (GROUND_GRIDSIZE + 1) * (GROUND_GRIDSIZE + 1);
    m_dwNumGroundIndices   = (GROUND_GRIDSIZE * GROUND_GRIDSIZE) * 6;
    m_pGroundVB            = NULL;
    m_pGroundIB            = NULL;
    m_planeGround          = D3DXPLANE( 0.0f, 1.0f, 0.0f, 0.0f );

    m_bDrawReflection      = FALSE;
    m_bCanDoAlphaBlend     = FALSE;
    m_bDrawHelp            = FALSE;

    ZeroMemory( m_bKey, 256 );
    m_vPosition      = D3DXVECTOR3( 0.0f, 3.0f,-4.0f );
    m_vVelocity      = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    m_fYaw           = 0.03f;
    m_fYawVelocity   = 0.0f;
    m_fPitch         = 0.5f;
    m_fPitchVelocity = 0.0f;
    D3DXMatrixTranslation( &m_matView, 0.0f, 0.0f, 10.0f );
    D3DXMatrixTranslation( &m_matOrientation, 0.0f, 0.0f, 0.0f );
}
*/



/*
HRESULT CMyD3DApplication::FrameMove()
{
    // Slow things down for the REF device
    if( m_d3dCaps.DeviceType == D3DDEVTYPE_REF )
        m_fElapsedTime = 0.05f;

    // Determine emitter position
    D3DXVECTOR3 vEmitterPostion( 0.0f, 0.0f, 0.f );
    if( m_bAnimateEmitter )
        vEmitterPostion = D3DXVECTOR3( 3*sinf(m_fTime), 0.0f, 3*cosf(m_fTime) );

    // Update particle system
    m_pParticleSystem->Update( m_fElapsedTime, m_dwNumParticlesToEmit,
                               g_clrColor[m_dwParticleColor],
                               g_clrColorFade[m_dwParticleColor], 8.0f,
                               vEmitterPostion );

    return S_OK;
}
*/


/*
HRESULT CMyD3DApplication::Render()
{
    // Update the camera here rather than in FrameMove() so you can
    // move the camera even when the scene is paused
    UpdateCamera();

    if( FAILED( m_pd3dDevice->BeginScene() ) )
        return S_OK;

    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                         0x00000000, 1.0f, 0L );

    // Draw reflection of particles
    if( m_bDrawReflection )
    {
        D3DXMATRIX matReflectedView;
        D3DXMatrixReflect( &matReflectedView, &m_planeGround );
        D3DXMatrixMultiply( &matReflectedView, &matReflectedView, &m_matView );        
    
        m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
        m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

        m_pd3dDevice->SetTransform( D3DTS_VIEW, &matReflectedView );
        m_pd3dDevice->SetTexture( 0, m_pParticleTexture );
        m_pParticleSystem->Render( m_pd3dDevice );

        m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
    }


    // Draw the ground
    if( m_bDrawReflection )
    {
        m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
        m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    }

    m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matView );
    m_pd3dDevice->SetTexture( 0, m_pGroundTexture );
    m_pd3dDevice->SetVertexShader( D3DFVF_PARTICLEVERTEX );
    m_pd3dDevice->SetStreamSource( 0, m_pGroundVB, sizeof(PARTICLEVERTEX) );
    m_pd3dDevice->SetIndices( m_pGroundIB, 0L );
    m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, m_dwNumGroundVertices, 0, m_dwNumGroundIndices/3 );


    // Draw particles
    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
    m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

    m_pd3dDevice->SetTexture(0, m_pParticleTexture );
    m_pParticleSystem->Render( m_pd3dDevice );

    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );


    // Output statistics
    m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
    m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );


    // Draw help
    if( m_bDrawHelp )
    {
        m_pFontSmall->DrawText( 2, 40, 0xffffffff,
                                _T("Keyboard controls:") );
        m_pFontSmall->DrawText( 20, 60, 0xffffffff,
                                _T("Move\nTurn\nPitch\nSlide\n\nHelp\n"
                                   "Change device\nAnimate emitter\n"
                                   "Change color\n\nToggle reflection\n"
                                   "Exit") );
        m_pFontSmall->DrawText( 160, 60, 0xffffffff,
                                _T("W,S\nE,Q\nA,Z\nArrow keys\n\n"
                                   "F1\nF2\nF3\nF4\n\nR\nEsc") );
    }
    else
        m_pFontSmall->DrawText( 2, 40, 0xffffffff,
                                _T("Press F1 for help") );

    
    // End the scene.
    m_pd3dDevice->EndScene();
    return S_OK;
}
*/



/*
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

    // Create textures
    if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, _T("Ground2.png"),
                                       &m_pGroundTexture ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, _T("Particle.png"),
                                       &m_pParticleTexture ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    // Set up the fonts and textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    // Check if we can do the reflection effect
    m_bCanDoAlphaBlend = (m_d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_SRCALPHA) &&
                         (m_d3dCaps.DestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA);

    if( m_bCanDoAlphaBlend )
        m_bDrawReflection = TRUE;

    // Create ground object
    {
        // Create vertex buffer for ground object
        hr = m_pd3dDevice->CreateVertexBuffer( m_dwNumGroundVertices*sizeof(PARTICLEVERTEX),
                                               D3DUSAGE_WRITEONLY, D3DFVF_PARTICLEVERTEX,
                                               D3DPOOL_MANAGED, &m_pGroundVB );
        if( FAILED(hr) )
            return E_FAIL;

        // Fill vertex buffer
        PARTICLEVERTEX* pVertices;
        if( FAILED( m_pGroundVB->Lock( 0, 0, (BYTE**)&pVertices, NULL ) ) )
            return hr;

        // Fill in vertices
        for( DWORD zz = 0; zz <= GROUND_GRIDSIZE; zz++ )
        {
            for( DWORD xx = 0; xx <= GROUND_GRIDSIZE; xx++ )
            {
                pVertices->v.x   = GROUND_WIDTH * (xx/(FLOAT)GROUND_GRIDSIZE-0.5f);
                pVertices->v.y   = 0.0f;
                pVertices->v.z   = GROUND_HEIGHT * (zz/(FLOAT)GROUND_GRIDSIZE-0.5f);
                pVertices->color = GROUND_COLOR;
                pVertices->tu    = xx*GROUND_TILE/(FLOAT)GROUND_GRIDSIZE;
                pVertices->tv    = zz*GROUND_TILE/(FLOAT)GROUND_GRIDSIZE;
                pVertices++;
            }
        }

        m_pGroundVB->Unlock();

        // Create the index buffer
        WORD* pIndices;
        hr = m_pd3dDevice->CreateIndexBuffer( m_dwNumGroundIndices*sizeof(WORD),
                                              D3DUSAGE_WRITEONLY,
                                              D3DFMT_INDEX16, D3DPOOL_MANAGED,
                                              &m_pGroundIB );
        if( FAILED(hr) )
            return E_FAIL;

        // Fill the index buffer
        m_pGroundIB->Lock( 0, m_dwNumGroundIndices*sizeof(WORD), (BYTE**)&pIndices, 0 );
        if( FAILED(hr) )
            return E_FAIL;

        // Fill in indices
        for( DWORD z = 0; z < GROUND_GRIDSIZE; z++ )
        {
            for( DWORD x = 0; x < GROUND_GRIDSIZE; x++ )
            {
                DWORD vtx = x + z * (GROUND_GRIDSIZE+1);
                *pIndices++ = (WORD)( vtx + 1 );
                *pIndices++ = (WORD)( vtx + 0 );
                *pIndices++ = (WORD)( vtx + 0 + (GROUND_GRIDSIZE+1) );
                *pIndices++ = (WORD)( vtx + 1 );
                *pIndices++ = (WORD)( vtx + 0 + (GROUND_GRIDSIZE+1) );
                *pIndices++ = (WORD)( vtx + 1 + (GROUND_GRIDSIZE+1) );
            }
        }

        m_pGroundIB->Unlock();
    }

    return S_OK;
}
*/


/*
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
	HRESULT hr;

    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    // Set the world matrix
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity( &matWorld );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set projection matrix
    D3DXMATRIX matProj;
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 0.1f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

    m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
    m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING,  FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE,  D3DCULL_CCW );
    m_pd3dDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );

    // Initialize the particle system
    if( FAILED( hr = m_pParticleSystem->RestoreDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    return S_OK;
}
*/


/*
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS8* pCaps, DWORD dwBehavior,
                                          D3DFORMAT Format )
{
    // Make sure device can do ONE:ONE alphablending
    if( 0 == ( pCaps->SrcBlendCaps & D3DPBLENDCAPS_ONE ) )
        return E_FAIL;
    if( 0 == ( pCaps->DestBlendCaps & D3DPBLENDCAPS_ONE ) )
        return E_FAIL;

    // Make sure HW TnL devices can do point sprites
    if( (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( pCaps->MaxPointSize <= 0.0f )
            return E_FAIL;
    }

    return S_OK;
}
*/



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CParticleSystem::CParticleSystem( DWORD dwFlush, DWORD dwDiscard, float fRadius )
{
    m_fRadius        = fRadius;

    m_dwBase         = dwDiscard;
    m_dwFlush        = dwFlush;
	m_dwDiscard      = dwDiscard;

    m_dwParticles    = 0;
    m_dwParticlesLim = 2048;

    m_pParticles     = NULL;
    m_pParticlesFree = NULL;
	m_pVB            = NULL;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CParticleSystem::~CParticleSystem()
{
	InvalidateDeviceObjects();

    while( m_pParticles )
    {
        PARTICLE* pSpark = m_pParticles;
        m_pParticles = pSpark->m_pNext;
        delete pSpark;
    }

    while( m_pParticlesFree )
    {
        PARTICLE *pSpark = m_pParticlesFree;
        m_pParticlesFree = pSpark->m_pNext;
        delete pSpark;
    }
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::RestoreDeviceObjects( LPDIRECT3DDEVICE8 pd3dDevice )
{
    HRESULT hr;

    // Create a vertex buffer for the particle system.  The size of this buffer
    // does not relate to the number of particles that exist.  Rather, the
    // buffer is used as a communication channel with the device.. we fill in 
    // a bit, and tell the device to draw.  While the device is drawing, we
    // fill in the next bit using NOOVERWRITE.  We continue doing this until 
    // we run out of vertex buffer space, and are forced to DISCARD the buffer
    // and start over at the beginning.

    if(FAILED(hr = pd3dDevice->CreateVertexBuffer( m_dwDiscard * 
		sizeof(PARTICLEPOINTVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, 
		D3DFVF_PARTICLEPOINTVERTEX, D3DPOOL_DEFAULT, &m_pVB )))
	{
        return E_FAIL;
	}

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pVB );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::Update( FLOAT fSecsPerFrame, DWORD dwNumParticlesToEmit,
                                 const D3DXCOLOR &clrEmitColor,
                                 const D3DXCOLOR &clrFadeColor, float fEmitVel,
                                 D3DXVECTOR3 vPosition )
{
    PARTICLE *pParticle, **ppParticle;
    static float fTime = 0.0f;
    fTime += fSecsPerFrame;

    ppParticle = &m_pParticles;

    while( *ppParticle )
    {
        pParticle = *ppParticle;

        // Calculate new position
        float fT = fTime - pParticle->m_fTime0;
        float fGravity;

        if( pParticle->m_bSpark )
        {
            fGravity = -5.0f;
            pParticle->m_fFade -= fSecsPerFrame * 2.25f;
        }
        else
        {
            fGravity = -9.8f;
            pParticle->m_fFade -= fSecsPerFrame * 8.25f;
        }

        pParticle->m_vPos    = pParticle->m_vVel0 * fT + pParticle->m_vPos0;
//        pParticle->m_vPos.y += (0.001f * fGravity) * (fT * fT);
//        pParticle->m_vVel.y  = pParticle->m_vVel0.y + fGravity * fT;

        if( pParticle->m_fFade < 0.0f )
            pParticle->m_fFade = 0.0f;

        // Kill old particles
        if( fT > 100)
        {

            // Kill particle
            *ppParticle = pParticle->m_pNext;
            pParticle->m_pNext = m_pParticlesFree;
            m_pParticlesFree = pParticle;

            if(!pParticle->m_bSpark)
                m_dwParticles--;
        }
        else
        {
            ppParticle = &pParticle->m_pNext;
        }
    }

    // Emit new particles
    DWORD dwParticlesEmit = m_dwParticles + dwNumParticlesToEmit;
    while( m_dwParticles < m_dwParticlesLim && m_dwParticles < dwParticlesEmit )
    {
        if( m_pParticlesFree )
        {
            pParticle = m_pParticlesFree;
            m_pParticlesFree = pParticle->m_pNext;
        }
        else
        {
            if( NULL == ( pParticle = new PARTICLE ) )
                return E_OUTOFMEMORY;
        }

        pParticle->m_pNext = m_pParticles;
        m_pParticles = pParticle;
        m_dwParticles++;

        // Emit new particle
        FLOAT fRand1 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 2.0f;
        FLOAT fRand2 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 0.25f;

        pParticle->m_bSpark = FALSE;

        pParticle->m_vPos0 = vPosition;

        pParticle->m_vVel0.x  = cosf(fRand1) * sinf(fRand2) * 2.5f;
        pParticle->m_vVel0.z  = sinf(fRand1) * sinf(fRand2) * 2.5f;
        pParticle->m_vVel0.y  = cosf(fRand2);
        pParticle->m_vVel0.y *= ((FLOAT)rand()/(FLOAT)RAND_MAX) * fEmitVel;

        pParticle->m_vPos = pParticle->m_vPos0;
        pParticle->m_vVel = pParticle->m_vVel0;

        pParticle->m_clrDiffuse = clrEmitColor;
        pParticle->m_clrFade    = clrFadeColor;
        pParticle->m_fFade      = 1.0f;
        pParticle->m_fTime0     = fTime;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the particle system using either pointsprites (if supported)
//       or using 4 vertices per particle
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::Render( LPDIRECT3DDEVICE8 pd3dDevice )
{
    HRESULT hr;

    // Set the render states for using point sprites
    pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE );
    pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );
    pd3dDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(8.08f) );
    pd3dDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(0.00f) );
    pd3dDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
    pd3dDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
    pd3dDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

    pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
    pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
    pd3dDevice->SetRenderState( D3DRS_LIGHTING,  FALSE );
    pd3dDevice->SetRenderState( D3DRS_CULLMODE,  D3DCULL_CCW );
    pd3dDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );

    // Set up the vertex buffer to be rendered
    pd3dDevice->SetStreamSource( 0, m_pVB, sizeof(PARTICLEPOINTVERTEX) );
    pd3dDevice->SetVertexShader( D3DFVF_PARTICLEPOINTVERTEX );

    PARTICLE*    pParticle = m_pParticles;
    PARTICLEPOINTVERTEX* pVertices;
    DWORD        dwNumParticlesToRender = 0;



	// Lock the vertex buffer.  We fill the vertex buffer in small
	// chunks, using D3DLOCK_NOOVERWRITE.  When we are done filling
	// each chunk, we call DrawPrim, and lock the next chunk.  When
	// we run out of space in the vertex buffer, we start over at
	// the beginning, using D3DLOCK_DISCARD.

	m_dwBase += m_dwFlush;

	if(m_dwBase >= m_dwDiscard)
		m_dwBase = 0;

	if(FAILED(hr = m_pVB->Lock(m_dwBase * sizeof(PARTICLEPOINTVERTEX), m_dwFlush * sizeof(PARTICLEPOINTVERTEX),
		(BYTE **) &pVertices, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD)))
    {
		return hr;
    }

		

    // Render each particle
    while( pParticle )
    {
        D3DXVECTOR3 vPos(pParticle->m_vPos);
        D3DXVECTOR3 vVel(pParticle->m_vVel);
        FLOAT       fLengthSq = D3DXVec3LengthSq(&vVel);
        UINT        dwSteps;

        if( fLengthSq < 1.0f )        dwSteps = 2;
        else if( fLengthSq <  4.00f ) dwSteps = 3;
        else if( fLengthSq <  9.00f ) dwSteps = 4;
        else if( fLengthSq < 12.25f ) dwSteps = 5;
        else if( fLengthSq < 16.00f ) dwSteps = 6;
        else if( fLengthSq < 20.25f ) dwSteps = 7;
        else                          dwSteps = 8;

        vVel *= -0.04f / (FLOAT)dwSteps;

        D3DXCOLOR clrDiffuse;
        D3DXColorLerp(&clrDiffuse, &pParticle->m_clrFade, &pParticle->m_clrDiffuse, pParticle->m_fFade);
        DWORD dwDiffuse = (DWORD) clrDiffuse;

        // Render each particle a bunch of times to get a blurring effect
        for( DWORD i = 0; i < dwSteps; i++ )
        {
            pVertices->v     = vPos;
            pVertices->color = 0xffffff00;
            pVertices++;

            if( ++dwNumParticlesToRender == m_dwFlush )
            {
                // Done filling this chunk of the vertex buffer.  Lets unlock and
                // draw this portion so we can begin filling the next chunk.

                m_pVB->Unlock();

                if(FAILED(hr = pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, m_dwBase, dwNumParticlesToRender)))
					return hr;

                // Lock the next chunk of the vertex buffer.  If we are at the 
                // end of the vertex buffer, DISCARD the vertex buffer and start
                // at the beginning.  Otherwise, specify NOOVERWRITE, so we can
                // continue filling the VB while the previous chunk is drawing.
				m_dwBase += m_dwFlush;

				if(m_dwBase >= m_dwDiscard)
					m_dwBase = 0;

				if(FAILED(hr = m_pVB->Lock(m_dwBase * sizeof(PARTICLEPOINTVERTEX), m_dwFlush * sizeof(PARTICLEPOINTVERTEX),
		            (BYTE **) &pVertices, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD)))
                {
					return hr;
                }

                dwNumParticlesToRender = 0;
            }

            vPos += vVel;
        }

        pParticle = pParticle->m_pNext;
    }

    // Unlock the vertex buffer
    m_pVB->Unlock();

    // Render any remaining particles
    if( dwNumParticlesToRender )
    {
        if(FAILED(hr = pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, m_dwBase, dwNumParticlesToRender )))
			return hr;
    }

    // Reset render states
    pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
    pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );

    return S_OK;
}

/* end of file */