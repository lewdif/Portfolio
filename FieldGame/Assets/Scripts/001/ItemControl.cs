using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemControl : MonoBehaviour
{
    private GameObject fencePos;

    void Start()
    {
        /*fencePos = GameObject.Find("Player/FencePos");

        if (gameObject.tag.Equals("Fence"))
        {
            Debug.Log(fencePos.transform.position);
            gameObject.transform.LookAt(fencePos.transform.position);
        }*/
    }

	void Update ()
    {
        if (gameObject.tag.Equals("Food"))
        {
            Destroy(gameObject, 5f);
        }
        else if (gameObject.tag.Equals("Wood"))
        {
            Destroy(gameObject, 4f);
        }
        else if (gameObject.tag.Equals("Stone"))
        {
            Destroy(gameObject, 7f);
        }
    }
}
