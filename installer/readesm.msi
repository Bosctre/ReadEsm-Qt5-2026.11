; Installer for ReadEsm-Qt5 (Windows x64). Called with:
;   makensis /DVERSION=2026.11 /DSTAGE=<dir> /DOUTFILE=<file> readesm.nsi
Unicode true
!include "MUI2.nsh"

Name "ReadEsm-Qt5 ${VERSION}"
OutFile "${OUTFILE}"
InstallDir "$PROGRAMFILES64\ReadEsm-Qt5"
InstallDirRegKey HKLM "Software\ReadEsm-Qt5" "InstallDir"
RequestExecutionLevel admin

!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_LICENSE "${STAGE}\doc\COPYING.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"

Section "ReadEsm-Qt5 (required)" SecMain
  SectionIn RO
  SetRegView 64
  SetOutPath "$INSTDIR"
  File /r "${STAGE}\*.*"

  WriteRegStr HKLM "Software\ReadEsm-Qt5" "InstallDir" "$INSTDIR"
  WriteUninstaller "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "DisplayName" "ReadEsm-Qt5 ${VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "DisplayVersion" "${VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "URLInfoAbout" "https://github.com/Bosctre/ReadEsm-Qt5-2026.11"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5" "NoRepair" 1
SectionEnd

Section "Start menu shortcut" SecMenu
  CreateDirectory "$SMPROGRAMS\ReadEsm-Qt5"
  CreateShortcut "$SMPROGRAMS\ReadEsm-Qt5\ReadEsm.lnk" "$INSTDIR\bin\readesm.exe"
  CreateShortcut "$SMPROGRAMS\ReadEsm-Qt5\Uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section "Open .ddd files with ReadEsm" SecAssoc
  SetRegView 64
  WriteRegStr HKLM "Software\Classes\.ddd" "" "ReadEsm.ddd"
  WriteRegStr HKLM "Software\Classes\ReadEsm.ddd" "" "Tachograph file (.ddd)"
  WriteRegStr HKLM "Software\Classes\ReadEsm.ddd\shell\open\command" "" '"$INSTDIR\bin\readesm.exe" "%1"'
  System::Call 'shell32::SHChangeNotify(i 0x08000000, i 0, p 0, p 0)'
SectionEnd

Section "Uninstall"
  SetRegView 64
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\ReadEsm-Qt5"
  DeleteRegKey HKLM "Software\ReadEsm-Qt5"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ReadEsm-Qt5"
  DeleteRegKey HKLM "Software\Classes\ReadEsm.ddd"
  DeleteRegKey HKLM "Software\Classes\.ddd"
  System::Call 'shell32::SHChangeNotify(i 0x08000000, i 0, p 0, p 0)'
SectionEnd
