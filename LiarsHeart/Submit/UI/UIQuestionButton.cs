using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.Events;

public class UIQuestionButton : MonoBehaviour
{
    [SerializeField] private Button button;
    [SerializeField] private TMP_Text questionIdText;

    public void Init(UIQuestionNode questionNode)
    {
        questionIdText.text = questionNode.GetId().ToString();
        questionNode.OnCompleteQuestion += CompleteQuestion;
    }

    public void AddButtonEvent(UnityAction call)
    {
        button.onClick.AddListener(call);
    }

    private void CompleteQuestion(bool value)
    {
        Image buttonImage = button.GetComponent<Image>();
        if(buttonImage != null)
        {
            if (value)
            {
                buttonImage.color = new Color32(0, 255, 126, 255);
                questionIdText.color = new Color32(0, 255, 126, 255);
            }
            else
            {
                buttonImage.color = new Color32(255, 255, 255, 255);
                questionIdText.color = new Color32(255, 255, 255, 255);
            }
        }
    }    
}
