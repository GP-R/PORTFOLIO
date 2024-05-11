using UnityEngine;
using TMPro;

public class UIInputQuestion : UIQuestionNode
{
    private TMP_InputField inputField;

    protected override void Start()
    {
        base.Start();
        Transform inputFieldRef = transform.Find("InputField");
        if (inputFieldRef != null)
        {
            inputField = inputFieldRef.GetComponent<TMP_InputField>();
            if (inputField != null)
            {
                if(inputField.text.Length > 0)
                {
                    SetQuestionComplete(true);
                }
                inputField.onEndEdit.AddListener((value) => CompleteQuestion(value));
            }
        }
    }

    public string GetQuestionResult()
    {
        return inputField.text;
    }

    public void SetInputFieldToSavedData(string text)
    {
        if (inputField == null)
        {
            Transform inputFieldRef = transform.Find("InputField");
            if (inputFieldRef != null)
            {
                inputField = inputFieldRef.GetComponent<TMP_InputField>();
            }
        }
        inputField.text = text;
    }

    private void CompleteQuestion(string value)
    {
        if(value.Length > 0)
        {
            SetQuestionComplete(true);
        }
        else
        {
            SetQuestionComplete(false);
        }
    }
}
