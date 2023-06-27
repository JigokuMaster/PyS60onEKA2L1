#include <coecntrl.h>
#include <aknappui.h>
#include <aknapp.h>
#include <akndoc.h>
#include <eikstart.h>
#include <bitstd.h>
#include <bitdev.h>
#include <e32std.h>
#include <e32base.h>
#include <fbs.h>
#include <w32std.h>



CFbsFont* createFont(TInt sz)
{

    CFbsFont* font;
    CFbsTypefaceStore* ts = CFbsTypefaceStore::NewL(NULL);
    
    CleanupStack::PushL(ts);
    
    //Font size determined visually
    TFontSpec spec(_L("Series 60 Sans"), sz);
    
    User::LeaveIfError(ts->GetNearestFontToDesignHeightInPixels((CFont*&)font, spec));
    //User::LeaveIfError(ts->GetNearestFontInTwips((CFont*&)font, spec));    
    CleanupStack::Pop(ts);
    return font;
}



const TUid KUidDrawApp={ 0xe000A0BC };


class CDrawWin : public CCoeControl
{
    public:
	void ConstructL(const TRect& aRect);
	~CDrawWin();
	RWindow& GetWindow() const;
	CFbsBitmap* iBitmap;
	void Draw(const TRect& aRect) const;
}; 


class CDrawApplication : public CAknApplication
{
    private:
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
};


class CDrawAppDocument : public CAknDocument
{
    public:
	CDrawAppDocument(CEikApplication& aApp): CAknDocument(aApp) { }

    private:
	CEikAppUi* CreateAppUiL();
};



class CDrawAppUi : public CAknAppUi
{

    public:
	void ConstructL();
	~CDrawAppUi();
	CDrawWin* iDrawWin;

};


void CDrawWin:: ConstructL(const TRect& aRect)	
{
    CreateWindowL();
    SetRect(aRect);
    ActivateL();

    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError(iBitmap->Create(TSize(230, 200), EColor16M));

    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(iBitmap);
    CleanupStack::PushL(bitmapDevice);


    /*
    CGraphicsContext* bitmapContext = NULL;
    User::LeaveIfError(bitmapDevice->CreateContext(bitmapContext));
    CleanupStack::PushL(bitmapContext);
    */
    

    CFbsBitGc *bitmapContext = CFbsBitGc::NewL();
    CleanupStack::PushL(bitmapContext);
    bitmapContext->Activate(bitmapDevice);


    TRect rect( 0 ,0 ,230 ,200 );
    bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
    bitmapContext->SetBrushColor(KRgbWhite);    
    bitmapContext->DrawRect(rect);
    

    /*
    CEikonEnv *env=CEikonEnv::Static();
    const CFont* font = env->NormalFont();
    */

    CFbsFont* font = createFont(14);

    bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
    bitmapContext->UseFont(font);
    bitmapContext->DrawText(_L("CFbsBitmap Text : "), TPoint(5, 20));
    bitmapContext->DrawText(_L("The quick brown fox jumped over the lazy dog"), TPoint(5, 60));
    bitmapContext->DiscardFont();
    
    
    CleanupStack::Pop(bitmapDevice);
    CleanupStack::Pop(bitmapContext);

}


RWindow& CDrawWin::GetWindow() const
{
    return Window();
}


void CDrawWin::Draw(const TRect& /*aRect*/) const
{

    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetPenColor(KRgbYellow);
    gc.SetBrushColor(KRgbYellow);    
    gc.DrawRect(Rect());

    if(iBitmap != NULL)
    {
	
 
        gc.DrawBitmap(TPoint( 10, 100), iBitmap);
        // gc.BitBlt(TPoint(10, 100), iBitmap);

    }
    else
    {
	gc.SetBrushColor(KRgbRed);
	gc.DrawRect(Rect());
    }
    
    const CFont* font = createFont(14);
    gc.UseFont(font);
    gc.SetBrushColor(KRgbBlue);    
    gc.SetPenColor(KRgbBlack);
    gc.DrawText(_L("RWindow Text : ") ,TPoint(10, 20));
    gc.DrawText(_L("The quick brown fox jumped over the lazy dog") ,TPoint(10, 40));    

}

CDrawWin::~CDrawWin()
{

    delete iBitmap;
    iBitmap = NULL;
}

void CDrawAppUi::ConstructL()
{

    BaseConstructL(CAknAppUi::EAknEnableSkin /* | ENoScreenFurniture*/ );
    iDrawWin = new (ELeave) CDrawWin;
    iDrawWin->ConstructL(ApplicationRect());
    // AddToStackL(iDrawWin);

}



CDrawAppUi::~CDrawAppUi()
{

    if ( iDrawWin != NULL )
    {
        // iEikonEnv->RemoveFromStack(iDrawWin);
        delete iDrawWin;
        iDrawWin = NULL;
    }    
}

CEikAppUi* CDrawAppDocument::CreateAppUiL()
{
    return new(ELeave) CDrawAppUi();
}


TUid CDrawApplication::AppDllUid() const
{
    return KUidDrawApp;
}


CApaDocument* CDrawApplication::CreateDocumentL()
{

    CDrawAppDocument* document = new (ELeave) CDrawAppDocument(*this);
    return document;
}
  
LOCAL_C CApaApplication* NewApplication()
{
    return new CDrawApplication;
}

GLDEF_C TInt E32Main()
{
    

    return EikStart::RunApplication(NewApplication);
}



