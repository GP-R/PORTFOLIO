using System.Collections.Generic;
using UnityEngine;

public class UISpot : MonoBehaviour
{
    [SerializeField] private int id;
    [SerializeField] private List<int> NextSpotId = new List<int>();

    private DialogueTrigger dialogueTrigger;

    private void OnEnable()
    {
        dialogueTrigger = gameObject.GetComponent<DialogueTrigger>();
        if (dialogueTrigger != null)
        {
            dialogueTrigger.endDialogueEvent.OnEventRaised += ActivateNextSpot;
        }
    }

    private void OnDisable()
    {
        if (dialogueTrigger != null)
        {
            dialogueTrigger.endDialogueEvent.OnEventRaised -= ActivateNextSpot;
        }
    }

    private void ActivateNextSpot()
    {
        foreach(int id in NextSpotId)
        {
            UISpot spot = GameManager.Map.GetSpotToId(id);
            if(spot != null)
            {
                spot.gameObject.SetActive(true);
                GameManager.Map.curActivatedSpot.Add(id);
            }
        }
        GameManager.Map.curActivatedSpot.Remove(id);
        this.gameObject.SetActive(false);
    }

    public int GetSpotId()
    {
        return id;
    }
}
