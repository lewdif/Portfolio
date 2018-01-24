using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class BtnMgr : MonoBehaviour
{
    private Button toTitle;
    RestClient rc = null;

    void Start()
    {
        rc = RestClient.Instance;
        toTitle = GameObject.Find("Canvas/Button").GetComponent<Button>();

        rc.Request("score.php", "post", (response) => {

            if (response["error"].Value != "no") return;

            print("score res: " + response["score"].Value);

        }, new Dictionary<string, string>() { { "score_res", StaticVal.SCORE + "" } });

        toTitle.onClick.AddListener(() =>
        {
            rc.Request("logout.php", "post", (response) =>
            {
                if (response["error"].Value != "no") return;

                print("logout res: " + response["error"].Value);

            });
            SceneManager.LoadScene("000");
        });
    }
}
