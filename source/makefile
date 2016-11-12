#
# pm library makefile
#

TOPDIR  = ..

!include $(TOPDIR)\config\makerules

all: $(TOPDIR)\lib\pm$(LBO) $(TOPDIR)\docs\pm.ctf $(MDUMMY)

OBJECTS = pm_error$(CO) pm_gui$(CO) pm_window$(CO) pm_frame$(CO)
OBJECTS = $(OBJECTS) pm_notebook$(CO) pm_profile$(CO) pm_fileutils$(CO)
OBJECTS = $(OBJECTS) pm_listbox$(CO) pm_combobox$(CO) pm_mutex$(CO)
OBJECTS = $(OBJECTS) pm_thread$(CO) pm_language$(CO) pm_mle$(CO)
OBJECTS = $(OBJECTS) pm_radiobutton$(CO) pm_checkbox$(CO) pm_filedialog$(CO)
OBJECTS = $(OBJECTS) pm_spinbutton$(CO) pm_splitcanvas$(CO) pm_rectangle$(CO)
OBJECTS = $(OBJECTS) pm_notify$(CO) pm_queue$(CO) pm_menu$(CO) pm_toolbar$(CO)
OBJECTS = $(OBJECTS) pm_entry$(CO) pm_label$(CO) pm_version$(CO)
OBJECTS = $(OBJECTS) pm_png$(CO) pm_titlebar$(CO) pm_helpwindow$(CO)
OBJECTS = $(OBJECTS) pm_button$(CO) pm_dirtree$(CO) pm_fileview$(CO)
OBJECTS = $(OBJECTS) pm_selectdir$(CO) pm_initfoc$(CO) pm_inittoolbar$(CO)
OBJECTS = $(OBJECTS) pm_initwindowset$(CO) pm_windowset$(CO) pm_nls$(CO)
OBJECTS = $(OBJECTS) pm_initnls$(CO) pm_exception$(CO) pm_tracer$(CO)
OBJECTS = $(OBJECTS) pm_initptracer$(CO) pm_groupbox$(CO) pm_font$(CO)
OBJECTS = $(OBJECTS) pm_2dimage$(CO) pm_debuglog$(CO)

IMPORTS = ++WinQueryControlColors.PMMERGE.5470

HEADERS = pm_error.h pm_gui.h pm_noncopyable.h pm_window.h pm_frame.h
HEADERS = $(HEADERS) pm_notebook.h pm_profile.h pm_listbox.h pm_combobox.h
HEADERS = $(HEADERS) pm_mutex.h pm_thread.h pm_language.h pm_mle.h
HEADERS = $(HEADERS) pm_radiobutton.h pm_checkbox.h pm_filedialog.h
HEADERS = $(HEADERS) pm_spinbutton.h pm_splitcanvas.h pm_rectangle.h
HEADERS = $(HEADERS) pm_container.h pm_notify.h pm_queue.h pm_menu.h
HEADERS = $(HEADERS) pm_toolbar.h pm_entry.h pm_label.h
HEADERS = $(HEADERS) pm_version.h pm_png.h pm_titlebar.h pm_helpwindow.h
HEADERS = $(HEADERS) pm_button.h pm_dirtree.h pm_fileview.h pm_selectdir.h
HEADERS = $(HEADERS) pm_delete.h pm_sharedptr.h pm_nls.h pm_tracer.h
HEADERS = $(HEADERS) pm_groupbox.h pm_font.h pm_2drawable.h pm_2dimage.h
HEADERS = $(HEADERS) pm_fileutils.h

$(TOPDIR)\lib\pm$(LBO): $(OBJECTS) makefile
  if exist $@ del $@
  $(LB) $@ $(OBJECTS) $(IMPORTS) $(LBENDL)

$(TOPDIR)\docs\pm.ctf: $(HEADERS)
  ccdoc -db $@ -nocdsm -norptpri $(HEADERS)
  ccdoc -db $@ -index
  ccdoc -db $@ -root "PM Library" -nowarn -norptdpv -rptmac1 -rptpro -norptsci -html $(TOPDIR)/docs/ -srcurl ../src

clean:  $(MDUMMY)
  -@del $(TOPDIR)\lib\pm$(LBO) $(OBJECTS) $(TOPDIR)\docs\pm.ctf $(TOPDIR)\docs\*.html 2> nul

pm_error$(CO):         pm_error.cpp pm_error.h pm_gui.h
pm_gui$(CO):           pm_gui.cpp pm_gui.h pm_error.h
pm_window$(CO):        pm_window.cpp pm_window.h pm_gui.h pm_error.h
pm_frame$(CO):         pm_frame.cpp pm_frame.h pm_window.h pm_gui.h pm_error.h
pm_notebook$(CO):      pm_notebook.cpp pm_notebook.h pm_window.h pm_gui.h pm_error.h
pm_profile$(CO):       pm_profile.cpp pm_profile.h pm_gui.h pm_error.h
pm_fileutils$(CO):     pm_fileutils.cpp pm_fileutils.h
pm_listbox$(CO):       pm_listbox.cpp pm_listbox.h pm_window.h pm_gui.h pm_error.h
pm_combobox$(CO):      pm_combobox.cpp pm_combobox.h pm_window.h pm_gui.h pm_error.h
pm_mutex$(CO):         pm_mutex.cpp pm_mutex.h
pm_thread$(CO):        pm_thread.cpp pm_thread.h pm_gui.h pm_error.h
pm_language$(CO):      pm_language.cpp pm_language.h
pm_mle$(CO):           pm_mle.cpp pm_mle.h pm_window.h pm_gui.h pm_error.h pm_font.h
pm_radiobutton$(CO):   pm_radiobutton.cpp pm_radiobutton.h pm_window.h pm_gui.h pm_error.h
pm_checkbox$(CO):      pm_checkbox.cpp pm_checkbox.h pm_window.h pm_gui.h pm_error.h
pm_filedialog$(CO):    pm_filedialog.cpp pm_filedialog.h pm_error.h pm_gui.h pm_frame.h
pm_spinbutton$(CO):    pm_spinbutton.cpp pm_spinbutton.h pm_window.h pm_gui.h pm_error.h
pm_splitcanvas$(CO):   pm_splitcanvas.cpp pm_splitcanvas.h pm_window.h pm_gui.h pm_error.h
pm_rectangle$(CO):     pm_rectangle.cpp pm_rectangle.h
pm_notify$(CO):        pm_notify.cpp pm_notify.h
pm_queue$(CO):         pm_queue.cpp pm_queue.h
pm_menu$(CO):          pm_menu.cpp pm_menu.h pm_error.h pm_gui.h
pm_tooolbar$(CO):      pm_tooolbar.cpp pm_tooolbar.h pm_inittoolbar.h pm_window.h pm_gui.h pm_error.h
pm_entry$(CO):         pm_entry.cpp pm_entry.h pm_window.h pm_gui.h pm_error.h
pm_label$(CO):         pm_label.cpp pm_label.h pm_window.h pm_gui.h pm_error.h
pm_version$(CO):       pm_version.cpp pm_version.h
pm_png$(CO):           pm_png.cpp pm_png.h pm_window.h pm_gui.h pm_error.h
pm_titlebar$(CO):      pm_titlebar.cpp pm_titlebar.h pm_window.h pm_gui.h pm_error.h
pm_helpwindow$(CO):    pm_helpwindow.cpp pm_helpwindow.h pm_window.h pm_error.h pm_gui.h
pm_button$(CO):        pm_button.cpp pm_button.h pm_window.h pm_gui.h pm_error.h
pm_dirtree$(CO):       pm_dirtree.cpp pm_dirtree.h pm_initfoc.h pm_window.h pm_gui.h pm_error.h
pm_fileview$(CO):      pm_fileview.cpp pm_fileview.h pm_initfoc.h pm_window.h pm_gui.h pm_error.h
pm_initfoc$(CO):       pm_initfoc.cpp pm_initfoc.h
pm_selectdir$(CO):     pm_selectdir.cpp pm_selectdir.h pm_window.h pm_error.h pm_gui.h
pm_inittoolbar$(CO):   pm_inittoolbar.cpp pm_inittoolbar.h
pm_initwindowset$(CO): pm_initwindowset.cpp pm_initwindowset.h
pm_windowset$(CO):     pm_windowset.cpp pm_windowset.h pm_initwindowset.h
pm_nls$(CO):           pm_nls.cpp pm_nls.h
pm_initnls$(CO):       pm_initnls.cpp pm_initnls.h
pm_exception$(CO):     pm_exception.cpp pm_exception.h
pm_tracer(CO):         pm_tracer.cpp pm_tracer.h pm_window.h pm_gui.h pm_error.h
pm_initptracer$(CO):   pm_initptracer.cpp pm_initptracer.h
pm_groupbox$(CO):      pm_groupbox.cpp pm_groupbox.h pm_window.h pm_gui.h pm_error.h
pm_font$(CO):          pm_font.cpp pm_font.h pm_error.h
pm_2dimage$(CO):       pm_2dimage.cpp  pm_2dimage.h  pm_2drawable.h
pm_debuglog$(CO):      pm_debuglog.cpp pm_debuglog.h
