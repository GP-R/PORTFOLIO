using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
using System.Collections;

public class UISubmit : UIPopup
{
    [SerializeField] private RectTransform nodeParent;
    public RectTransform NodeParent { get => nodeParent; }

    [SerializeField] private Button resetButton;
    [SerializeField] private Button closeButton;
    [SerializeField] private Button submitButton;

    [SerializeField] private Transform buttonParent;
    [SerializeField] private UIQuestionButton questionButton;

    private UIQuestionNode[] questionNodes;
    private Coroutine curCoroutine = default;

    private void Start()
    {
        questionNodes = nodeParent.GetComponentsInChildren<UIQuestionNode>(false);
        SetQuestionNodeToSavedData();
        for (int i = questionNodes.Length - 1; i >= 0; i--)
        {
            UIQuestionButton button = Instantiate(questionButton, buttonParent);
            button.Init(questionNodes[i]);

            Vector3 zoomScale = new Vector3(2.0f, 2.0f, 1.0f);
            Vector3 zoomPosition = questionNodes[i].transform.localPosition;
            button.AddButtonEvent(() => OnClickQuestionButton(zoomScale, zoomPosition));
        }

        Vector3 originalScale = nodeParent.localScale;
        Vector3 originalPosition = nodeParent.localPosition;
        resetButton.onClick.AddListener(()=>OnClickQuestionButton(originalScale, originalPosition));
        closeButton.onClick.AddListener(SaveAndClose);
        submitButton.onClick.AddListener(SubmitAnswer);
    }

    private void OnClickQuestionButton(Vector3 targetScale, Vector3 targetPosition)
    {
        if(curCoroutine != null)
        {
            return;
        }
        curCoroutine = StartCoroutine(ZoomNode(targetScale, targetPosition));
    }

    private IEnumerator ZoomNode(Vector3 targetScale, Vector3 targetPosition)
    {
        float duration = 0.5f;
        float currentTime = 0f;

        Vector3 startScale = nodeParent.localScale;
        Vector3 startPosition = nodeParent.localPosition;

        targetPosition.x = targetPosition.x * targetScale.x;
        targetPosition.y = targetPosition.y * targetScale.y;

        while (currentTime < duration)
        {
            nodeParent.localScale = Vector3.Lerp(startScale, targetScale, currentTime / duration);

            float xPos = Mathf.Lerp(startPosition.x, -targetPosition.x, currentTime / duration);
            float yPos = Mathf.Lerp(startPosition.y, -targetPosition.y, currentTime / duration);
            nodeParent.localPosition = new Vector3(xPos, yPos, startPosition.z);

            currentTime += Time.deltaTime;
            yield return null;
        }

        nodeParent.localScale = targetScale;
        nodeParent.localPosition = new Vector3(-targetPosition.x, -targetPosition.y, startPosition.z);
        curCoroutine = null;
    }

    private void SaveAndClose()
    {
        foreach(UIQuestionNode questionNode in questionNodes)
        {
            GameManager.Submit.SaveNodeData(questionNode);
        }
        SetVisible(false);
    }

    private void SetQuestionNodeToSavedData()
    {
        foreach (UIQuestionNode questionNode in questionNodes)
        {
            UISelectQuestion selectQuestion = questionNode as UISelectQuestion;
            if (selectQuestion != null)
            {
                if(selectQuestion.QuestionNodeSO != null)
                {
                    List<int> prevAnswer = GameManager.Submit.GetToggleNodeData(selectQuestion.QuestionNodeSO.Id);
                    if(prevAnswer != null)
                    {
                        for(int i = 0; i < prevAnswer.Count; i++)
                        {
                            selectQuestion.QuestionToggles[prevAnswer[i] - 1].Toggle.isOn = true;
                        }
                    }
                }
            }

            UIInputQuestion inputQuestion = questionNode as UIInputQuestion;
            if (inputQuestion != null)
            {
                if(inputQuestion.QuestionNodeSO != null)
                {
                    string prevAnswer = GameManager.Submit.GetTextNodeData(inputQuestion.QuestionNodeSO.Id);
                    if(prevAnswer != null)
                    {
                        inputQuestion.SetInputFieldToSavedData(prevAnswer);
                    }
                }
            }
        }

        GameManager.Submit.ClearNodes();
    }

    private void SubmitAnswer()
    {
        foreach (UIQuestionNode questionNode in questionNodes)
        {
            GameManager.Submit.SaveNodeData(questionNode);
        }
        GameManager.Submit.CompareResult();
    }
}
