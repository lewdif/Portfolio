using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayerControl : MonoBehaviour
{
    private AudioSource burnSound;
    public AudioClip burning;
    
    private AudioSource eatSound;
    public AudioClip chomp;
    private Animator animator;

    private bool freezePos;
    public bool canAim;

    public static float MOVE_AREA_RADIUS = 15.0f; // 섬의 반지름.
    public static float MOVE_SPEED = 7.0f; // 이동 속도.

    public GameObject FencePrefab;

    //private GameObject fencePos;

    private struct Key
    { // 키 조작 정보 구조체
        public bool up; // ↑
        public bool down; // ↓
        public bool right; // →
        public bool left; // ←
        public bool pick; // 줍는다／버린다.
        public bool action; // 먹는다 / 수리한다.
        public bool eat;
        public bool destroy;
    };

    private Key key; // 키 조작 정보를 보관하는 변수.

    public enum STEP
    { // 플레이어의 상태를 나타내는 열거체.
        NONE = -1, // 상태 정보 없음.
        MOVE = 0, // 이동 중.
        GROWFIRE, // 나무 넣는 중.
        EATING, // 식사 중.
        NUM, // 상태가 몇 종류 있는지 나타낸다(=3).
    };

    public STEP step = STEP.NONE; // 현재 상태.
    public STEP nextStep = STEP.NONE; // 다음 상태.
    public float stepTimer = 0.0f;

    // 다음 네 개의 멤버 변수를 PlayerControl class에 추가.
    private GameObject closestItem = null; // 플레이어의 정면에 있는 GameObject.
    private GameObject carriedItem = null; // 플레이어가 들어올린 GameObject.
    private ItemRoot itemRoot = null; // ItemRoot 스크립트를 가짐.

    private GameObject closestEvent = null; // 주목하고 있는 이벤트를 저장.
    private EventRoot eventRoot = null; // EventRoot 클래스를 사용하기 위한 변수.
    private GameObject campFire = null; // 모닥불의 모델을 사용하기 위한 변수.
    private GameStatus gameStatus = null;

    private int stone;
    private int wood;
    private int food;

    private int hp;

    private bool isPushed;

    void Start()
    {
        burnSound = this.gameObject.AddComponent<AudioSource>();
        burnSound.clip = burning;
        burnSound.loop = false;

        eatSound = this.gameObject.AddComponent<AudioSource>();
        eatSound.clip = chomp;
        eatSound.loop = false;

        hp = 3;
        stone = 0;
        wood = 5;
        food = 2;



        freezePos = false;
        canAim = true;
        isPushed = false;

        step = STEP.NONE; // 현 단계 상태를 초기화.
        nextStep = STEP.MOVE;
        itemRoot = GameObject.Find("GameRoot").GetComponent<ItemRoot>();
        eventRoot = GameObject.Find("GameRoot").GetComponent<EventRoot>();
        gameStatus = GameObject.Find("GameRoot").GetComponent<GameStatus>();
        campFire = GameObject.Find("Fire/CampFire/Fire");
        //fencePos = GameObject.Find("Player/FencePos");

        animator = GameObject.Find("Player/Yuko").GetComponent<Animator>();
        GameObject.Find("Canvas/Food").GetComponent<Text>().text = "" + food;
        GameObject.Find("Canvas/Stone").GetComponent<Text>().text = "" + stone;
        GameObject.Find("Canvas/Wood").GetComponent<Text>().text = "" + wood;
    }
    
    void Update()
    {
        HPControl();
        getInput(); // 입력 정보 취득.
        // 상태가 변화했을 때------------.
        animator.SetBool("IsHit", false);
        //freezePos = false;

        if (hp <= 0)
        {
            SceneManager.LoadScene("002");
        }

        stepTimer += Time.deltaTime;
        float eatTime = 0.5f; // 사과는 2초에 걸쳐 먹는다.
        float growFireTime = 0.5f; // 수리에 걸리는 시간도 2초.

        // 상태를 변화시킨다---------------------.
        if (nextStep == STEP.NONE)
        { // 다음 예정이 없으면.
            switch (step)
            {
                case STEP.MOVE: // '이동 중' 상태의 처리.
                    do
                    {
                        if (food > 0)
                        {
                            if (key.eat)
                            {
                                nextStep = STEP.EATING;
                            }
                        }

                        if (!key.action)
                        { // 액션 키가 눌려있지 않다.
                            break; // 루프 탈출.
                        }

                        // 주목하는 이벤트가 있을 때.
                        if (closestEvent != null)
                        {
                            if (!isEventIgnitable())
                            { // 이벤트를 시작할 수 없으면.
                                break; // 아무 것도 하지 않는다.
                            }

                            // 이벤트 종류를 가져온다.
                            Event.TYPE ignitable_event = eventRoot.getEventType(closestEvent);
                            switch (ignitable_event)
                            {
                                case Event.TYPE.GROWFIRE:
                                    nextStep = STEP.GROWFIRE;
                                    break;
                            }
                            break;
                        }
                    } while (false);
                    break;
                case STEP.EATING: // '식사 중' 상태의 처리.
                    if (stepTimer > eatTime)
                    { // 2초 대기.
                        nextStep = STEP.MOVE; // '이동' 상태로 이행.
                    }
                    break;
                case STEP.GROWFIRE: // '수리 중' 상태의 처리.
                    if (stepTimer > growFireTime)
                    { // 2초 대기.
                        nextStep = STEP.MOVE; // '이동' 상태로 이행.
                    }
                    break;
            }
        }
        while (nextStep != STEP.NONE)
        { // 상태가 NONE이외 = 상태가 변화했다.
            step = nextStep;
            nextStep = STEP.NONE;
            switch (step)
            {
                case STEP.MOVE:
                    break;

                case STEP.EATING:
                    UseFood();
                    break;

                case STEP.GROWFIRE:
                    UseWood();
                    break;
            }
            stepTimer = 0.0f;
        }

        // 각 상황에서 반복할 것----------.
        switch (step)
        {
            case STEP.MOVE:
                moveControl();
                pickDropControl();
                // 이동 가능한 경우는 항상 배가 고파진다.
                gameStatus.alwaysSatiety();
                gameStatus.alwaysFire();
                break;

            case STEP.GROWFIRE:
                StartCoroutine(growFire());
                break;
        }

        if (Input.GetKey(KeyCode.V))
        {
            isPushed = true;
        }

        if (Input.GetKeyUp(KeyCode.V))
        {
            isPushed = false;
        }

        mousePick();
    }

    private void mousePick()
    {
        if (canAim.Equals(false)) { return; }

        if (Input.GetMouseButtonDown(0))
        {
            animator.SetBool("IsShoot", true);
            freezePos = true;
        }

        if (Input.GetMouseButton(0))
        {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                transform.LookAt(new Vector3(hit.point.x, 1, hit.point.z));
            }
        }

        if (Input.GetMouseButtonUp(0))
        {
            animator.SetBool("IsShoot", false);
            freezePos = false;
        }
        
        if (Input.GetMouseButton(1))
        {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                transform.LookAt(new Vector3(hit.point.x, 1, hit.point.z));
            }
        }

        if (Input.GetMouseButtonUp(1))
        {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                transform.LookAt(new Vector3(hit.point.x, 1, hit.point.z));

                if(wood > 2)
                {
                    Vector3 playerPos = gameObject.transform.position;
                    Vector3 newPos = new Vector3(playerPos.x, 0.75f, playerPos.z);
                    Vector3 playerDirection = gameObject.transform.forward;
                    Quaternion playerRotation = gameObject.transform.rotation;
                    float spawnDistance = 2f;

                    Vector3 spawnPos = newPos + playerDirection * spawnDistance;

                    GameObject go = Instantiate(FencePrefab, spawnPos, playerRotation);

                    wood -= 3;
                    GameObject.Find("Canvas/Wood").GetComponent<Text>().text = "" + wood;
                    //go.transform.Rotate(new Vector3(0, 90, 0));

                    /*GameObject go = GameObject.Instantiate(FencePrefab) as GameObject;
                    go.transform.position = gameObject.transform.position;
                    //go.transform.LookAt(new Vector3(hit.point.x, 0, hit.point.z));

                    Vector3 pos = new Vector3(dir.x, dir.y - 1.0f, dir.z);
                    Debug.Log(rot.y);
                    Quaternion qut = new Quaternion(0, rot.y, 0, rot.w);
                    go.transform.rotation = qut;
                    go.transform.position = pos;*/
                }
            }
        }
    }

    private IEnumerator growFire()
    {
        float scaleX = campFire.transform.localScale.x;
        float scaleY = campFire.transform.localScale.y;
        float scaleZ = campFire.transform.localScale.z;

        for (float f = scaleX; f < scaleX + 0.5f; f += 0.1f)
        {
            campFire.transform.localScale = new Vector3(scaleX + 0.1f, scaleY + 0.1f, campFire.transform.localScale.z);
        }

        yield return new WaitForSeconds(0.5f);

        scaleX = campFire.transform.localScale.x;
        scaleY = campFire.transform.localScale.y;
        scaleZ = campFire.transform.localScale.z;

        for (float f = scaleX; f > scaleX - 0.5f; f -= 0.1f)
        {
            campFire.transform.localScale = new Vector3(scaleX - 0.1f, scaleY - 0.1f, campFire.transform.localScale.z);
        }

        yield return null;
    }

    // 키 입력을 조사해 그 결과를 바탕으로 맴버 변수 key의 값을 갱신한다.
    private void getInput()
    {
        if (freezePos.Equals(true)) { return; }

        key.up = false;
        key.down = false;
        key.right = false;
        key.left = false;

        // ↑키가 눌렸으면 true를 대입.
        key.up |= Input.GetKey(KeyCode.W);
        // ↓키가 눌렸으면 true를 대입.
        key.down |= Input.GetKey(KeyCode.S);
        // →키가 눌렸으면 true를 대입.
        key.right |= Input.GetKey(KeyCode.D);
        // ←키가 눌렸으면 true를 대입..
        key.left |= Input.GetKey(KeyCode.A);
        // Space 키가 눌렸으면 true를 대입.
        key.pick = Input.GetKeyDown(KeyCode.Space);
        // F 키가 눌렸으면 true를 대입.
        key.action = Input.GetKeyDown(KeyCode.F);

        key.eat = Input.GetKeyDown(KeyCode.C);

        key.destroy = Input.GetKey(KeyCode.V);
    }

    // 키 입력에 따라 실제로 이동시키는 처리를 한다.
    private void moveControl()
    {
        Vector3 moveVector = Vector3.zero; // 이동용 벡터.
        Vector3 position = transform.position; // 현재 위치를 보관.
        //bool isMoved = false;

        if (key.right)
        { // →키가 눌렸으면.
            moveVector += Vector3.right; // 이동용 벡터를 오른쪽으로 향한다.
            animator.SetBool("IsRun", true);
            //isMoved = true; // '이동 중' 플래그.
            canAim = false;
        }

        if (key.left)
        {
            moveVector += Vector3.left;
            animator.SetBool("IsRun", true);
            //isMoved = true;
            canAim = false;
        }

        if (key.up)
        {
            moveVector += Vector3.forward;
            animator.SetBool("IsRun", true);
            //isMoved = true;
            canAim = false;
        }

        if (key.down)
        {
            moveVector += Vector3.back;
            animator.SetBool("IsRun", true);
            //isMoved = true;
            canAim = false;
        }

        if (key.right.Equals(false) && key.left.Equals(false) && key.up.Equals(false) && key.down.Equals(false))
        {
            animator.SetBool("IsRun", false);
            canAim = true;
        }

        moveVector.Normalize(); // 길이를 1로.
        moveVector *= MOVE_SPEED * Time.deltaTime; // 속도×시간＝거리.
        position += moveVector; // 위치를 이동.
        position.y = 0.0f; // 높이를 0으로 한다.

        // 세계의 중앙에서 갱신한 위치까지의 거리가 섬의 반지름보다 크면.
        if (position.magnitude > MOVE_AREA_RADIUS)
        {
            position.Normalize();
            position *= MOVE_AREA_RADIUS; // 위치를 섬의 끝자락에 머물게 한다.
        }
        // 새로 구한 위치(position)의 높이를 현재 높이로 되돌린다.
        position.y = transform.position.y;
        // 실제 위치를 새로 구한 위치로 변경한다.
        transform.position = position;
        // 이동 벡터의 길이가 0.01보다 큰 경우.
        // =어느 정도 이상의 이동한 경우.
        if (moveVector.magnitude > 0.01f)
        {
            // 캐릭터의 방향을 천천히 바꾼다.
            Quaternion q = Quaternion.LookRotation(moveVector, Vector3.up);
            transform.rotation = Quaternion.Lerp(transform.rotation, q, 0.1f);
        }

        moveVector.Normalize(); // 길이를 1로.
        moveVector *= MOVE_SPEED * Time.deltaTime; // 속도×시간＝거리.
        position += moveVector; // 위치를 이동.
        position.y = 0.0f; // 높이를 0으로 한다.

        // 세계의 중앙에서 갱신한 위치까지의 거리가 섬의 반지름보다 크면.
        if (position.magnitude > MOVE_AREA_RADIUS)
        {
            position.Normalize();
            position *= MOVE_AREA_RADIUS; // 위치를 섬의 끝자락에 머물게 한다.
        }

        if (moveVector.magnitude > 0.01f)
        {
            // 캐릭터의 방향을 천천히 바꾼다.
            Quaternion q = Quaternion.LookRotation(moveVector, Vector3.up);
            transform.rotation = Quaternion.Lerp(transform.rotation, q, 0.2f);
        }
    }

    void OnTriggerStay(Collider other)
    {
        GameObject otherGo = other.gameObject;
        // 트리거의 GameObject 레이어 설정이 Item이라면.
        if (otherGo.layer == LayerMask.NameToLayer("Item"))
        {
            // 아무 것도 주목하고 있지 않으면.
            if (closestItem == null)
            {
                if (isOtherInView(otherGo))
                { // 정면에 있으면.
                    closestItem = otherGo; // 주목한다.
                }
                // 뭔가 주목하고 있으면.
            }
            else if (closestItem == otherGo)
            {
                if (!isOtherInView(otherGo))
                { // 정면에 없으면.
                    closestItem = null; // 주목을 그만둔다.
                }
            }
        }
        // 트리거의 GameObject의 레이어 설정이 Event라면.
        else if (otherGo.layer == LayerMask.NameToLayer("Event"))
        {
            // 아무것도 주목하고 있지 않으면.
            if (closestEvent == null)
            {
                if (isOtherInView(otherGo))
                { // 정면에 있으면.
                    closestEvent = otherGo; // 주목한다.
                }
                // 뭔가에 주목하고 있으면.
            }
            else if (closestEvent == otherGo)
            {
                if (!isOtherInView(otherGo))
                { // 정면에 없으면.
                    closestEvent = null; // 주목을 그만둔다.
                }
            }
        }

        if (other.gameObject.tag.Equals("Fence"))
        {
            if (key.destroy)
            {
                Debug.Log("!!");
                GetWoodFromFence();
                Destroy(other.gameObject);
            }
        }
    }

    // 들고 있는 아이템의 종류와 주목하는 이벤트의 종류를 보고 이벤트 시작
    private bool isEventIgnitable()
    {
        bool ret = false;
        do
        {
            if (closestEvent == null)
            { // 주목 이벤트가 없으면.
                break; // false를 반환한다.
            }

            // 들고 있는 아이템 종류와 주목하는 이벤트의 종류에서.
            // 이벤트가 가능한지 판정하고, 이벤트 불가라면 false를 반환한다.
            if (!eventRoot.isEventIgnitable(wood, closestEvent))
            {
                break;
            }

            ret = true; // 여기까지 오면 이벤트를 시작할 수 있다고 판정!.
        } while (false);

        return (ret);
    }

    // 주목을 그만두게 한다.
    void OnTriggerExit(Collider other)
    {
        if (closestItem == other.gameObject)
        {
            closestItem = null; // 주목을 그만둔다.
        }
    }

    private void pickDropControl()
    {
        do
        {
            if (!key.pick)
            { // '줍기/버리기'키가 눌리지 않았으면.
                break; // 아무것도 하지 않고 메소드 종료.
            }

            if (closestItem == null)
            {// 주목 중인 아이템이 없으면.
                break; // 아무것도 하지 않고 메소드 종료.
            }

            if (closestItem.tag.Equals("Stone"))
            {
                stone++;

                itemRoot.loadBullet();

                GameObject.Find("Canvas/Stone").GetComponent<Text>().text = "" + stone;
            }

            if (closestItem.tag.Equals("Food"))
            {
                food++;

                GameObject.Find("Canvas/Food").GetComponent<Text>().text = "" + food;
            }

            if (closestItem.tag.Equals("Wood"))
            {
                wood++;

                GameObject.Find("Canvas/Wood").GetComponent<Text>().text = "" + wood;
            }

            GameObject.Destroy(closestItem);
        } while (false);
    }

    // 접촉한 물건이 자신의 정면에 있는지 판단한다.
    private bool isOtherInView(GameObject other)
    {
        bool ret = false;
        do
        {
            Vector3 heading = // 자신이 현재 향하고 있는 방향을 보관.
            transform.TransformDirection(Vector3.forward);
            Vector3 toOther = // 자신 쪽에서 본 아이템의 방향을 보관.
            other.transform.position - transform.position;
            heading.y = 0.0f;
            toOther.y = 0.0f;
            heading.Normalize(); // 길이를 1로 하고 방향만 벡터로.
            toOther.Normalize(); // 길이를 1로 하고 방향만 벡터로.
            float dp = Vector3.Dot(heading, toOther); // 양쪽 벡터의 내적을 취득.
            if (dp < Mathf.Cos(45.0f))
            { // 내적이 45도인 코사인 값 미만이면.
                break; // 루프를 빠져나간다.
            }
            ret = true; // 내적이 45도인 코사인 값 이상이면 정면에 있다.
        } while (false);
        return (ret);
    }

    public void UseBullet()
    {
        stone--;
        GameObject.Find("Canvas/Stone").GetComponent<Text>().text = "" + stone;
    }

    public void UseFood()
    {
        eatSound.Play();
        gameStatus.addSatiety(0.3f);
        food--;
        GameObject.Find("Canvas/Food").GetComponent<Text>().text = "" + food;
    }

    public void UseWood()
    {
        burnSound.Play();
        gameStatus.addFire(0.1f);
        wood--;
        GameObject.Find("Canvas/Wood").GetComponent<Text>().text = "" + wood;
    }

    public void GetWoodFromFence()
    {
        wood += 1;
        GameObject.Find("Canvas/Wood").GetComponent<Text>().text = "" + wood;
    }

    public void Damaged()
    {
        hp--;
        animator.SetBool("IsHit", true);

        HPControl();
    }

    public void HPControl()
    {
        if (hp == 3)
        {
            GameObject.Find("Canvas/Life0").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Life1").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Life2").GetComponent<Image>().enabled = true;
        }
        else if (hp == 2)
        {
            GameObject.Find("Canvas/Life0").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Life1").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Life2").GetComponent<Image>().enabled = false;
        }
        else if (hp == 1)
        {
            GameObject.Find("Canvas/Life0").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Life1").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/Life2").GetComponent<Image>().enabled = false;
        }
        else if (hp == 0)
        {
            animator.SetBool("IsDead", true);
            GameObject.Find("Canvas/Life0").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/Life1").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/Life2").GetComponent<Image>().enabled = false;
        }
    }

    public int GetHP()
    {
        return hp;
    }

    public void AddHP()
    {
        hp++;
    }
}
