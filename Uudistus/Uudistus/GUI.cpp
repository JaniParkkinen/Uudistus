//#include "GUI.h"
//
//GUI::GUI()
//{
//    //nothing yet
//}
//
//void GUI::draw(sf::RenderTarget* rt)
//{
//    if (m_visible)
//    {
//        for (std::pair<std::string, GUIArea> area : m_areas)
//        {
//            area.second.draw(rt);
//        }
//    }
//}
//
//void GUI::update()
//{
//    if (m_visible && m_active)
//    {
//        for (std::pair<std::string, GUIArea> area : m_areas)
//        {
//            area.second.update();
//        }
//    }
//}
//
//void GUI::setActive(bool active)
//{
//    m_active = active;
//}
//
//void GUI::setVisible(bool visible)
//{
//    m_visible = visible;
//}