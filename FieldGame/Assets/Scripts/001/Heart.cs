using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Heart : MonoBehaviour
{
    PlayerControl playerCtrl;
    private float rotateSpeed;
    private bool isCol;

    void Start()
    {
        rotateSpeed = 50.0f;
        isCol = false;
        playerCtrl = GameObject.Find("Player").GetComponent<PlayerControl>();
    }

    void Update()
    {
        transform.Rotate(Vector3.up, rotateSpeed * Time.deltaTime, Space.World);
        
        if (playerCtrl.GetHP() < 3 && isCol == true)
        {
            playerCtrl.AddHP();

            Destroy(gameObject);
        }
    }

    void OnTriggerEnter(Collider target)
    {
        if (target.gameObject.tag.Equals("Player"))
        {
            isCol = true;
        }
    }
}
