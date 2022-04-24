/************************************************************
!
!	File: fallbacks.h - fallback resources for program lxb.
!
!		Same as the Application defaults file Lxb-ad
!		Same caution in Netscape-ad applies to this file.
!
!		Copyright 2002  Bruce E. 
!
!	"Lxb*fontList: 8x13bold", 
!
!	4/2022:
!	commented geometry is for "fixed" default font
!	fonts have changed since i started this project - lxb.
!
*************************************************************/

String fallbacks[] = {
/*
! program defaults
*/
	"Lxb*background: gray",
	"Lxb*fontList: 8x13bold",
	"Lxb*XmText.translations: #override\n <Key>osfDelete: delete-previous-character()",
	"Lxb*XmTextField.translations: #override\n <Key>osfDelete: delete-previous-character()",
/*
! main GUI window
*/
/*
	"Lxb.geometry: +337+0",
*/
	"Lxb.geometry: +382+0",
	"Lxb*main_window*msg_area.background:	white",
/*
! widget hierarchy display window
*/	
	"Lxb*wtree.width: 410",
	"Lxb*wtree.height: 325",
	"Lxb*wtree*tree*background: SlateGray",
	"Lxb*wtree*tree*foreground:	white",
	"Lxb*wtree*panner*shadowThickness: 1",
	"Lxb*wtree*panner*background: SlateGray",
/*
! widget pallet window
*/
/*
	"Lxb*pallet_shell.geometry: 230x490+98+0",
*/

	"Lxb*pallet_shell.geometry: 275x455+98+0",
/*
! resource editor window
*/
/*
	"Lxb*editor_shell.geometry: +756+0",
*/
	"Lxb*editor_shell.geometry: +796+0",
	"Lxb*editor_shell*XmTextField.width: 200",
/*
! Application being built
*/
/*
	"Lxb.topLevelShell.geometry: 260x385+325+470",
*/

	"Lxb.topLevelShell.geometry: 260x385+425+450",
	"Lxb.topLevelShell*translations: <Key>: noop()",
	NULL
};
