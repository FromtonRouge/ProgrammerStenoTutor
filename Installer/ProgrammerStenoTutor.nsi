; ProgrammerStenoTutor.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install ProgrammerStenoTutor.nsi into a directory that the user selects,

;--------------------------------

!define ORGANIZATION_NAME "FromtonRouge"
!define APPLICATION_NAME "ProgrammerStenoTutor"

; The name of the installer
Name "${APPLICATION_NAME}"

!define /date TIMESTAMP "%Y-%m-%d"

; The file to write
OutFile "${TIMESTAMP}-unstable-${APPLICATION_NAME}.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\${ORGANIZATION_NAME}\${APPLICATION_NAME}"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "${APPLICATION_NAME} (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "..\build-ProgrammerStenoTutor-Desktop_Qt_5_9_1_MSVC2015_64bit-Release\release\${APPLICATION_NAME}.exe"

  File "..\install\Qt5Core.dll"
  File "..\install\Qt5Gui.dll"
  File "..\install\Qt5Widgets.dll"

  ; Platforms plugin
  SetOutPath $INSTDIR\platforms
  File "..\install\platforms\qwindows.dll"

  ; Write the installation path into the registry
  WriteRegStr HKLM "Software\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "DisplayName" "${APPLICATION_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ORGANIZATION_NAME}\${APPLICATION_NAME}" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\${APPLICATION_NAME}"
  CreateShortCut "$SMPROGRAMS\${APPLICATION_NAME}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\${APPLICATION_NAME}\${APPLICATION_NAME}.lnk" "$INSTDIR\${APPLICATION_NAME}.exe" "" "$INSTDIR\${APPLICATION_NAME}.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${ORGANIZATION_NAME}\${APPLICATION_NAME}"
  DeleteRegKey HKLM "Software\${ORGANIZATION_NAME}\${APPLICATION_NAME}"

  ; Remove files and uninstaller

  Delete "$INSTDIR\${APPLICATION_NAME}.exe"

  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"

  Delete "$INSTDIR\uninstall.exe"

  Delete "$INSTDIR\platforms\qwindows.dll"
  RMDir "$INSTDIR\platforms"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\${APPLICATION_NAME}\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\${APPLICATION_NAME}"
  RMDir "$INSTDIR"

SectionEnd