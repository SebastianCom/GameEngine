#include "CoreHeaders.h"

#include "EventManager.h"
#include "Event.h"
#include "GameCore.h"

namespace fw {

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
    while( m_EventQueue.empty() == false )
    {
        Event* pEvent = m_EventQueue.front();
        m_EventQueue.pop();

        delete pEvent;
    }
}

void EventManager::AddEvent(Event* pEvent)
{
    m_EventQueue.push( pEvent );
}

void EventManager::ProcessEvents()
{
    while( m_EventQueue.empty() == false )
    {
        Event* pEvent = m_EventQueue.front();
        m_EventQueue.pop();

        if( m_EventListeners.find( pEvent->GetEventType() ) != m_EventListeners.end() )
        {
            for( EventListener* pListener : m_EventListeners[pEvent->GetEventType()] )
            {
                pListener->OnEvent( pEvent );
            }
        }

        delete pEvent;
    }
}

void EventManager::RegisterForEvents(const char* eventType, EventListener* pListener)
{
    m_EventListeners[eventType].push_back( pListener );
}

void EventManager::UnregisterForEvents(const char* eventType, EventListener* pListener)
{
    if( m_EventListeners.find( eventType ) == m_EventListeners.end() )
        return;

    std::vector<EventListener*>& list = m_EventListeners[eventType];
    list.erase( std::remove(list.begin(), list.end(), pListener), list.end() );
}

} // namespace fw
