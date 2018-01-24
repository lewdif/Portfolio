using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.SceneManagement;

public class SceneControl : MonoBehaviour
{
    // 아래 변수 추가
    private GameStatus game_status = null;
    private PlayerControl player_control = null;

    public enum STEP
    { // 게임 상태.
        NONE = -1, // 상태 정보 없음.
        PLAY = 0, // 플레이 중.
        CLEAR, // 클리어 상태.
        GAMEOVER, // 게임 오버 상태.
        NUM, // 상태가 몇 종류인지 나타낸다(=3).
    };
    public STEP step = STEP.NONE; // 현대 단계.
    public STEP next_step = STEP.NONE; // 다음 단계.
    //public float step_timer = 0.0f; // 타이머.
    private float clear_time = 0.0f; // 클리어 시간.

    void Start ()
    {
        game_status = gameObject.GetComponent<GameStatus>();
        player_control =
        GameObject.Find("Player").GetComponent<PlayerControl>();
        step = STEP.PLAY;
        next_step = STEP.PLAY;
    }

    // 게임을 클리어했는지 또는 게임 오버인지 판정하고 게임 상태를 전환
    void Update()
    {
        //step_timer += Time.deltaTime;

        if (next_step == STEP.NONE)
        {
            switch (step)
            {
                case STEP.PLAY:
                    /*if (game_status.isGameClear())
                    {
                        // 클리어 상태로 이동.
                        next_step = STEP.CLEAR;
                    }*/

                    if (game_status.isGameOver())
                    {
                        SceneManager.LoadScene("002");
                        // 게임 오버 상태로 이동.
                        //next_step = STEP.GAMEOVER;
                    }
                    break;
                // 클리어 시 및 게임 오버 시의 처리.
                case STEP.CLEAR:
                case STEP.GAMEOVER:
                    /*if (Input.GetMouseButtonDown(0))
                    {
                        // 마우스 버튼이 눌렸으면 GameScene을 다시 읽는다.
                        //SceneManager.LoadScene("GameScene");
                    }*/
                    break;
            }
        }
        while (next_step != STEP.NONE)
        {
            step = next_step;
            next_step = STEP.NONE;
            switch (step)
            {
                case STEP.CLEAR:
                    // PlayerControl을 제어 불가로.
                    player_control.enabled = false;
                    // 현재의 경과 시간으로 클리어 시간을 갱신.
                    //clear_time = step_timer;
                    break;
                case STEP.GAMEOVER:
                    // PlayerControl를 제어 불가.
                    player_control.enabled = false;
                    break;
            }
        }
        //GameObject.Find("Canvas/Time").GetComponent<Text>().text = "TIME : " + step_timer.ToString("N2");
        //StaticVal.SetScore((int)step_timer);
    }
}
