//
// Created by aleksander on 23.02.24.
//

#ifndef BASSPLAY_2_DPIAWAREFRAME_H
#define BASSPLAY_2_DPIAWAREFRAME_H

#include <wx/wx.h>

namespace Bassplay::Ui {
    class DpiAwareFrame : public wxFrame {
    public:
        DpiAwareFrame(wxWindow *parent,
                      wxWindowID id,
                      const wxString &title,
                      const wxPoint &pos = wxDefaultPosition,
                      const wxSize &size = wxDefaultSize,
                      long style = wxDEFAULT_FRAME_STYLE,
                      const wxString &name = wxFrameNameStr) : wxFrame(parent, id, title,
                                                                       pos, size, style,
                                                                       name) {
            InitRatio();
            SetClientSize(CalculateRealSize(const_cast<wxSize &>(size)));
        }

        DpiAwareFrame() { InitRatio(); };

        ~DpiAwareFrame() override { delete mRatio; }

    protected:
        wxSize *mRatio = nullptr;

        wxSize CalculateRealSize(wxSize &originalSize) {
            return {mRatio->x * originalSize.x, mRatio->y * originalSize.y};
        };

        void InitRatio() { mRatio = new wxSize(GetTextExtent("M")); }
    };
}


#endif //BASSPLAY_2_DPIAWAREFRAME_H
