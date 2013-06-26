# define the name of the installer
SetCompressor /FINAL /SOLID lzma 
outfile "Cape2Fluent.exe"
 
# define the directory to install to, the desktop in this case as specified  
# by the predefined $DESKTOP variable
installDir "c:\Cape2Fluent"
Page components
Page directory
Page instfiles
# default section
Section "VC Redistributable 2008"
	ClearErrors
	ExecWait "$EXEDIR\vcredist_x86.exe" $0
	DetailPrint "some program returned $0"
	IfErrors 0 +2
		messageBox MB_OK "Installation of VC Redist failed. Check if the file vcredist_x86.exe is present in installator directory or install it manually."
	
SectionEnd

Section "Cape2Fluent"

	# g³ówny katalog
	setOutPath $INSTDIR
	file Cape2Fluent\*.*
		
	setOutPath $INSTDIR
	
	RegDLL cape2fluent.dll
	
	writeUninstaller $INSTDIR\uninstall.exe
	
	WriteRegStr HKCU "Software\Cape2Fluent" "InstallDir" "$INSTDIR"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "Name" "Cape2Fluent"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "Description" "Cape-Open 2 Fluent port"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "CapeVersion" "1.0"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "ComponentVersion" "1.0"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "VendorURL" "baniuk@zut.edu.pl"
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription" "About" "(c) Piotr Baniukiewicz"
	
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\Implemented Categories\{678C09A1-7D66-11D2-A67D-00105A42887F}" "" ""
	WriteRegStr HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\Implemented Categories\{678C09A5-7D66-11D2-A67D-00105A42887F}" "" ""

	# create a shortcut named "new shortcut" in the start menu programs directory
    # presently, the new shortcut doesn't call anything (the second field is blank)
	CreateDirectory "$SMPROGRAMS\Cape2Fluent"
    createShortCut "$SMPROGRAMS\Cape2Fluent\Params.lnk" "$INSTDIR\params.txt"
	createShortCut "$SMPROGRAMS\Cape2Fluent\uninstall.lnk" "$INSTDIR\uninstall.exe"
 SectionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"
 
# Always delete uninstaller first
	delete "$INSTDIR\uninstall.exe"

    delete "$SMPROGRAMS\Cape2Fluent\Params.lnk"
	delete "$SMPROGRAMS\Cape2Fluent\uninstall.lnk"
	RMDir "$SMPROGRAMS\Cape2Fluent"
	UnRegDLL cape2fluent.dll
	DeleteRegKey HKCU "Software\Cape2Fluent"
	DeleteRegKey HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\CapeDescription"
	DeleteRegKey HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}\Implemented Categories"
	DeleteRegKey HKCR "CLSID\{687728BA-9FC0-4F97-A143-EBEE0735C18F}"

# now delete installed file
	messageBox MB_OK "Please, delete Cape2Fluent installation directory manually"
SectionEnd