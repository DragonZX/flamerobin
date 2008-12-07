/*
  Copyright (c) 2004-2008 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

//-----------------------------------------------------------------------------
#ifndef FR_BASEFRAME_H
#define FR_BASEFRAME_H

#include <wx/wx.h>

#include <map>
//-----------------------------------------------------------------------------
// Base class for all the frames in FlameRobin. Implements storing and restoring
// of settings in config and other commonalities.
class BaseFrame: public wxFrame {
protected:
    // Reads any settings from config. The predefined implementation reads
    // size and position of the frame based on getStorageName(). No need to call
    // it directly except when wanting to "reload" the saved settings.
    void readConfigSettings();
    // Use this to customize which settings are read from config().
    virtual void doReadConfigSettings(const wxString& prefix);
    // Writes any settings to config. The predefined implementation saves
    // size and position of the frame based on getStorageName(). No need to call
    // it directly except when wanting to save settings without destroying the
    // frame.
    void writeConfigSettings() const;
    // Use this to customize which settings are written to config().
    virtual void doWriteConfigSettings(const wxString& prefix) const;
    // Returns the name of the frame for storage purpose.
    // A frame that wants its settings stored and retrieved must override this
    // function and return a nonempty wxString. The predefined implementation
    // returns getName().
    virtual const wxString getStorageName() const;
    // Returns the name of the frame, which can be the same for all instances
    // of the class or different for each instance. Currently it isn't really
    // used except as a base for getStorageName().
    // The predefined implementation returns "".
    virtual const wxString getName() const;
    // Returns the default position and size for the frame; it's called by
    // readConfigSettings() to get first-time default position and size.
    // The predefined implementation returns -1 for all 4 items.
    virtual const wxRect getDefaultRect() const;
public:
    BaseFrame(wxWindow* parent, int id, const wxString& title);
    virtual ~BaseFrame();

    virtual bool Show(bool show = TRUE);
    virtual bool Destroy();
private:
    // event handling
    void OnClose(wxCloseEvent& event);

    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif // FR_BASEFRAME_H
