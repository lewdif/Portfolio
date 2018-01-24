using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item
{
    public enum TYPE
    { // 아이템 종류.
        NONE = -1, // 없음.
        STONE = 0, // 철광석.
        FOOD, // 사과.
        WOOD, // 식물.
        NUM, // 아이템이 몇 종류인가 나타낸다(=3).
    };
};

public class ItemRoot : MonoBehaviour
{
    private AudioSource audio;
    public AudioClip shoot;
    //private PlayerControl playerCtrl;

    private GameObject player;
    public GameObject StonePrefab = null;
    public GameObject WoodPrefab = null;
    public GameObject FoodPrefab = null;
    public GameObject BulletPrefab = null;

    private Vector3 dir;
    private bool isFired;

    public List<GameObject> BULLETS;

    public float step_timer = 0.0f;

    public static float RESPAWN_TIME_FOOD = 8.0f; // 사과 출현 시간 상수.
    public static float RESPAWN_TIME_STONE = 9.0f; // 철광석 출현 시간 상수.
    public static float RESPAWN_TIME_WOOD = 7.0f; // 식물 출현 시간 상수.

    private float respawnTimerFood = 0.0f; // 사과의 출현 시간.
    private float respawnTimerStone = 0.0f; // 철광석의 출현 시간.
    private float respawnTimerWood = 0.0f; // 식물의 출현 시간.

    // 아이템의 종류를 Item.TYPE형으로 반환하는 메소드.
    public Item.TYPE getItemType(GameObject item_go)
    {
        Item.TYPE type = Item.TYPE.NONE;
        if (item_go != null)
        { // 인수로 받은 GameObject가 비어있지 않으면.
            switch (item_go.tag)
            { // 태그로 분기.
                case "Stone": type = Item.TYPE.STONE; break;
                case "Food": type = Item.TYPE.FOOD; break;
                case "Wood": type = Item.TYPE.WOOD; break;
            }
        }
        return (type);
    }
    
    void Start()
    {
        audio = this.gameObject.AddComponent<AudioSource>();
        audio.clip = shoot;
        audio.loop = false;
        //playerCtrl = GameObject.Find("Player").GetComponent<PlayerControl>();
        BULLETS = new List<GameObject>();
        player = GameObject.Find("Player");
        dir = new Vector3();
        isFired = false;
    }
    
    void Update()
    {
        respawnTimerFood += Time.deltaTime;
        respawnTimerStone += Time.deltaTime;
        respawnTimerWood += Time.deltaTime;
        if (respawnTimerFood > RESPAWN_TIME_FOOD)
        {
            respawnTimerFood = 0.0f;
            respawnFOOD(); // 사과를 출현시킨다.
        }
        if (respawnTimerStone > RESPAWN_TIME_STONE)
        {
            respawnTimerStone = 0.0f;
            respawnStone(); // 철광석을 출현시킨다.
        }
        if (respawnTimerWood > RESPAWN_TIME_WOOD)
        {
            respawnTimerWood = 0.0f;
            respawnWood(); // 식물을 출현시킨다.
        }

        if (BULLETS.Count > 0)
        {
            GameObject bullet = BULLETS[BULLETS.Count - 1];

            if (isFired.Equals(true))
            {
            }
            else
            {
                if (Input.GetMouseButtonUp(0))
                {
                    if (player.GetComponent<PlayerControl>().canAim)
                    {
                        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                        RaycastHit hit;
                        dir = GameObject.Find("Player/Aim").transform.position;

                        if (Physics.Raycast(ray, out hit))
                        {
                            audio.Play();
                            bullet.transform.position = player.transform.position;
                            bullet.SetActive(true);
                            bullet.transform.LookAt(new Vector3(hit.point.x, bullet.transform.position.y, hit.point.z));
                        }
                        player.GetComponent<PlayerControl>().UseBullet();
                        isFired = true;
                    }
                }
            }

            bullet.transform.position = Vector3.MoveTowards(bullet.transform.position, dir, 20 * Time.deltaTime);

        }
    }

    public void respawnStone()
    {
        GameObject go = GameObject.Instantiate(StonePrefab) as GameObject;
        Vector3 pos = new Vector3(Random.Range(-8.5f, 8.5f), 0.0f, Random.Range(-8.5f, 8.5f));
        go.transform.position = pos;
        Quaternion rot = Quaternion.Euler(new Vector3(0, Random.Range(0.0f, 360.0f), 0));
        go.transform.rotation = rot;
    }
    
    public void respawnFOOD()
    {
        GameObject go = GameObject.Instantiate(FoodPrefab) as GameObject;
        Vector3 pos = new Vector3(Random.Range(-8.5f, 8.5f), 1.0f, Random.Range(-8.5f, 8.5f));
        go.transform.position = pos;
    }
    
    public void respawnWood()
    {
        GameObject go = GameObject.Instantiate(WoodPrefab) as GameObject;
        Vector3 pos = new Vector3(Random.Range(-8.5f, 8.5f), 1.0f, Random.Range(-8.5f, 8.5f));
        go.transform.position = pos;
    }

    public void loadBullet()
    {
        GameObject go = GameObject.Instantiate(BulletPrefab) as GameObject;

        //go.SetActive(false);

        AddBullet(go);
    }

    public void AddBullet(GameObject go)
    {
        BULLETS.Add(go);
    }

    public void RemoveBullet()
    {
        if (BULLETS.Count.Equals(0))
        {
            return;
        }

        isFired = false;
        BULLETS.RemoveAt(BULLETS.Count - 1);
    }
    
    public void ShootingCtrl(bool isfired)
    {
        isFired = isfired;
    }
}
