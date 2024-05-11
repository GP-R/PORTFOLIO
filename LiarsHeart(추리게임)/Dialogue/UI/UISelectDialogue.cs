using UnityEngine;
using UnityEngine.UI;
using TMPro;
using DS.ScriptableObjects;
using DS.Data;

public class UISelectDialogue : UIPopup
{
    [SerializeField] private RectTransform parent;
    [SerializeField] private GameObject selectButtonPrefab;

    //Listening
    [SerializeField] private DialogueEventChannelSO selectDialogueEvent;
    
    private void OnEnable()
    {
        selectDialogueEvent.OnEventRaised += OpenSelectDialogueUI;
    }

    private void OnDisable()
    {
        selectDialogueEvent.OnEventRaised -= OpenSelectDialogueUI;
    }

    private void OpenSelectDialogueUI(DSDialogueSO dialogueSO)
    {
        foreach(DSDialogueChoiceData option in dialogueSO.Choices)
        {
            CreateSelectButton(option);
        }
    }
    
    private void CreateSelectButton(DSDialogueChoiceData selectOption)
    {
        UISelectButton button = Instantiate(selectButtonPrefab, parent).GetComponent<UISelectButton>();
        if(selectOption.IsSelected)
        {
            button.GetComponent<Button>().interactable = false;
            button.SetUnSelectable();
        }
        button.GetComponent<Button>().onClick.AddListener(() => OnClickSelectButton(selectOption));
        button.SetButtonText(selectOption.Text);
    }

    private void OnClickSelectButton(DSDialogueChoiceData selectOption)
    {
        //TODO
        if(!selectOption.InCorrect)
        {
            GameManager.Dialogue.InCorrectSelect();
        }
        selectOption.IsSelected = true;
        if (selectOption.NextDialogue != null)
        {
            GameManager.Dialogue.PlayDialogue(selectOption.NextDialogue);
        }
        GameManager.UI.ClosePopupUI(this);
    }
}
