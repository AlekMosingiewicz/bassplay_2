//
// Created by aleksander on 23.02.24.
//

#ifndef BASSPLAY_2_DPIAWAREFRAME_HPP
#define BASSPLAY_2_DPIAWAREFRAME_HPP

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

        ~DpiAwareFrame() override { delete m_Ratio; }

    protected:
        wxSize *m_Ratio = nullptr;

        wxSize CalculateRealSize(wxSize &originalSize) {
            return {m_Ratio->x * originalSize.x, m_Ratio->y * originalSize.y};
        };

        void InitRatio() { m_Ratio = new wxSize(GetTextExtent("M")); }
    };
}


#endif //BASSPLAY_2_DPIAWAREFRAME_HPP
