using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DS.ScriptableObjects;
using UnityEngine.EventSystems;

public class DialogueTrigger : MonoBehaviour
{
    [SerializeField] private DSDialogueContainerSO startDialogue;
    public VoidEventChannelSO endDialogueEvent;

    private UIDialogue DialogueUI = default;

    private void OnEnable()
    {
        endDialogueEvent.OnEventRaised += EndDialogueEvent;
    }

    private void OnDisable()
    {
        endDialogueEvent.OnEventRaised -= EndDialogueEvent;
    }

    public void OnDialogueTrigger()
    {
        if(this.gameObject.GetComponent<Button>() != null)
        {
            EventSystem.current.SetSelectedGameObject(null);
        }
        startDialogue.InitDialogueContainer();

        DialogueUI = GameManager.UI.LoadPopupUI<UIDialogue>("Dialogue");
        DialogueUI.SetVisible(true);

        GameManager.Dialogue.PlayDialogue(startDialogue.GetStartDialogue());
    }

    private void EndDialogueEvent()
    {
        if(DialogueUI != null)
        {
            GameManager.UI.ClosePopupUI(DialogueUI);
        }
    }
}
