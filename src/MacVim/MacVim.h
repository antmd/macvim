/* vi:set ts=8 sts=4 sw=4 ft=objc:
 *
 * VIM - Vi IMproved		by Bram Moolenaar
 *				MacVim GUI port by Bjorn Winckler
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 * See README.txt for an overview of the Vim source code.
 */

#import <Cocoa/Cocoa.h>
#import <asl.h>

#import "MMLog.h"
#import "MMCocoaCategories.h"
#import "MMVimBackendProtocol.h"

// Taken from /usr/include/AvailabilityMacros.h
#ifndef MAC_OS_X_VERSION_10_4
# define MAC_OS_X_VERSION_10_4 1040
#endif
#ifndef MAC_OS_X_VERSION_10_5
# define MAC_OS_X_VERSION_10_5 1050
#endif
#ifndef MAC_OS_X_VERSION_10_6
# define MAC_OS_X_VERSION_10_6 1060
#endif
#ifndef MAC_OS_X_VERSION_10_7
# define MAC_OS_X_VERSION_10_7 1070
#endif


//
// This is the protocol MMAppController implements.
//
// It handles connections between MacVim and Vim and communication from Vim to
// MacVim.
//
// Do not add methods to this interface without a _very_ good reason (if
// possible, instead add a new message to the *MsgID enum below and pass it via
// processInput:forIdentifier).  Methods should not modify the state directly
// but should instead delay any potential modifications (see
// connectBackend:pid: and processInput:forIdentifier:).
//
@protocol MMAppProtocol
- (unsigned)connectBackend:(byref in id <MMBackendProtocol>)proxy pid:(int)pid;
- (oneway void)processInput:(in bycopy NSArray *)queue
              forIdentifier:(unsigned)identifier;
- (NSArray *)serverList;
@end


//
// The following enum lists all messages that are passed between MacVim and
// Vim.  These can be sent in processInput:data: and in processCommandQueue:.
//

// NOTE! This array must be updated whenever the enum below changes!
extern char *MessageStrings[];

enum {
    OpenWindowMsgID = 1,    // NOTE: FIRST IN ENUM MUST BE 1
    KeyDownMsgID,
    BatchDrawMsgID,
    SelectTabMsgID,
    CloseTabMsgID,
    AddNewTabMsgID,
    DraggedTabMsgID,
    UpdateTabBarMsgID,
    ShowTabBarMsgID,
    HideTabBarMsgID,
    SetTextRowsMsgID,
    SetTextColumnsMsgID,
    SetTextDimensionsMsgID,
    LiveResizeMsgID,
    SetTextDimensionsReplyMsgID,
    SetWindowTitleMsgID,
    ScrollWheelMsgID,
    MouseDownMsgID,
    MouseUpMsgID,
    MouseDraggedMsgID,
    FlushQueueMsgID,
    AddMenuMsgID,
    AddMenuItemMsgID,
    RemoveMenuItemMsgID,
    EnableMenuItemMsgID,
    ExecuteMenuMsgID,
    ShowToolbarMsgID,
    ToggleToolbarMsgID,
    CreateScrollbarMsgID,
    DestroyScrollbarMsgID,
    ShowScrollbarMsgID,
    SetScrollbarPositionMsgID,
    SetScrollbarThumbMsgID,
    ScrollbarEventMsgID,
    SetFontMsgID,
    SetWideFontMsgID,
    VimShouldCloseMsgID,
    SetDefaultColorsMsgID,
    ExecuteActionMsgID,
    DropFilesMsgID,
    DropStringMsgID,
    ShowPopupMenuMsgID,
    GotFocusMsgID,
    LostFocusMsgID,
    MouseMovedMsgID,
    SetMouseShapeMsgID,
    AdjustLinespaceMsgID,
    ActivateMsgID,
    SetServerNameMsgID,
    EnterFullScreenMsgID,
    LeaveFullScreenMsgID,
    SetBuffersModifiedMsgID,
    AddInputMsgID,
    SetPreEditPositionMsgID,
    TerminateNowMsgID,
    XcodeModMsgID,
    EnableAntialiasMsgID,
    DisableAntialiasMsgID,
    SetVimStateMsgID,
    SetDocumentFilenameMsgID,
    OpenWithArgumentsMsgID,
    CloseWindowMsgID,
    SetFullScreenColorMsgID,
    ShowFindReplaceDialogMsgID,
    FindReplaceMsgID,
    ActivateKeyScriptMsgID,
    DeactivateKeyScriptMsgID,
    EnableImControlMsgID,
    DisableImControlMsgID,
    ActivatedImMsgID,
    DeactivatedImMsgID,
    BrowseForFileMsgID,
    ShowDialogMsgID,
    NetBeansMsgID,
    SetMarkedTextMsgID,
    ZoomMsgID,
    SetWindowPositionMsgID,
    DeleteSignMsgID,
    SetTooltipMsgID,
    SetTooltipDelayMsgID,
    GestureMsgID,
    AddToMRUMsgID,
    LastMsgID   // NOTE: MUST BE LAST MESSAGE IN ENUM!
};


enum {
    ClearAllDrawType = 1,
    ClearBlockDrawType,
    DeleteLinesDrawType,
    DrawStringDrawType,
    InsertLinesDrawType,
    DrawCursorDrawType,
    SetCursorPosDrawType,
    DrawInvertedRectDrawType,
    DrawSignDrawType,
};

enum {
    MMInsertionPointBlock,
    MMInsertionPointHorizontal,
    MMInsertionPointVertical,
    MMInsertionPointHollow,
    MMInsertionPointVerticalRight,
};


enum {
    ToolbarLabelFlag = 1,
    ToolbarIconFlag = 2,
    ToolbarSizeRegularFlag = 4
};


enum {
    MMTabLabel = 0,
    MMTabToolTip,
    MMTabInfoCount
};

enum {
    MMGestureSwipeLeft,
    MMGestureSwipeRight,
    MMGestureSwipeUp,
    MMGestureSwipeDown,
};


// Create a string holding the labels of all messages in message queue for
// debugging purposes (condense some messages since there may typically be LOTS
// of them on a queue).
NSString *debugStringForMessageQueue(NSArray *queue);


// Shared user defaults (most user defaults are in Miscellaneous.h).
// Contrary to the user defaults in Miscellaneous.h these defaults are not
// intitialized to any default values.  That is, unless the user sets them
// these keys will not be present in the user default database.

// Argument used to stop MacVim from opening an empty window on startup
// (techincally this is a user default but should not be used as such).
extern NSString *MMNoWindowKey;

extern NSString *MMAutosaveRowsKey;
extern NSString *MMAutosaveColumnsKey;
extern NSString *MMRendererKey;

enum {
    MMRendererDefault = 0,
    MMRendererATSUI,
    MMRendererCoreText
};


extern NSString *VimFindPboardType;

// ODB Editor Suite Constants (taken from ODBEditorSuite.h)
#define	keyFileSender		'FSnd'
#define	keyFileSenderToken	'FTok'
#define	keyFileCustomPath	'Burl'
#define	kODBEditorSuite		'R*ch'
#define	kAEModifiedFile		'FMod'
#define	keyNewLocation		'New?'
#define	kAEClosedFile		'FCls'
#define	keySenderToken		'Tokn'


// MacVim Apple Event Constants
#define keyMMUntitledWindow       'MMuw'




#ifndef NSINTEGER_DEFINED
// NSInteger was introduced in 10.5
# if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
# else
typedef int NSInteger;
typedef unsigned int NSUInteger;
# endif
# define NSINTEGER_DEFINED 1
#endif

#ifndef NSAppKitVersionNumber10_4  // Needed for pre-10.5 SDK
# define NSAppKitVersionNumber10_4 824
#endif

#ifndef CGFLOAT_DEFINED
    // On Leopard, CGFloat is float on 32bit and double on 64bit. On Tiger,
    // we can't use this anyways, so it's just here to keep the compiler happy.
    // However, when we're compiling for Tiger and running on Leopard, we
    // might need the correct typedef, so this piece is copied from ATSTypes.h
# ifdef __LP64__
    typedef double CGFloat;
# else
    typedef float CGFloat;
# endif
#endif

