using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public static float MOVE_AREA_RADIUS = 15.0f; // 섬의 반지름.

    private PlayerControl playerCtrl;
    private GameObject player;
    private ItemRoot itemRoot = null;

    void Start ()
    {
        player = GameObject.Find("Player");
        playerCtrl = player.GetComponent<PlayerControl>();
        gameObject.SetActive(false);
        itemRoot = GameObject.Find("GameRoot").GetComponent<ItemRoot>();
    }

	void Update ()
    {
        Vector3 position = transform.position;

        if (position.magnitude > MOVE_AREA_RADIUS)
        {
            position.Normalize();

            itemRoot.RemoveBullet();
            Destroy(gameObject);
        }
    }

    void OnTriggerEnter(Collider target)
    {
        if (target.gameObject.tag.Equals("Monster"))
        {
            itemRoot.RemoveBullet();
            Destroy(gameObject);
        }
    }
}
