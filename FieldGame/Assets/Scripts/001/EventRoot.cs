using UnityEngine;
using System.Collections;

public class Event
{ // 이벤트 종류.
    public enum TYPE
    {
        NONE = -1, // 없음.
        GROWFIRE = 0, // 모닥불 키우기.
        NUM, // 이벤트가 몇 종류 있는지 나타낸다(=1).
    };
};

public class EventRoot : MonoBehaviour
{
    public Event.TYPE getEventType(GameObject event_go)
    {
        Event.TYPE type = Event.TYPE.NONE;
        if (event_go != null)
        { // 인수의 GameObject가 비어있지 않으면.
            if (event_go.tag == "CampFire")
            {
                type = Event.TYPE.GROWFIRE;
            }
        }
        return (type);
    }

    // 모닥불에 접촉했는지 확인
    public bool isEventIgnitable(int woodCnt, GameObject event_go)
    {
        bool ret = false;
        Event.TYPE type = Event.TYPE.NONE;

        if (event_go != null)
        {
            type = getEventType(event_go); // 이벤트 타입을 구한다.
        }

        switch (type)
        {
            case Event.TYPE.GROWFIRE:
                if (woodCnt > 0)
                { // 가지고 있는 것이 식물이라면.
                    ret = true; // '이벤트할 수 있어요！'라고 응답한다.
                }
                break;
        }
        return (ret);
    }

    // 지정된 게임 오브젝트의 이벤트 타입 반환
    public string getIgnitableMessage(GameObject event_go)
    {
        string message = "";
        Event.TYPE type = Event.TYPE.NONE;
        if (event_go != null)
        {
            type = getEventType(event_go);
        }
        switch (type)
        {
            case Event.TYPE.GROWFIRE:
                message = "수리한다";
                break;
        }
        return (message);
    }
}
