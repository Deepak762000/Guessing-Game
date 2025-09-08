async function makeGuess() {
  const guess = document.getElementById("guess").value;
  if (!guess) return;

  try {
    const res = await fetch(`http://localhost:8080/check/${guess}`);
    if (!res.ok) throw new Error("Server error");
    const data = await res.json(); 

    const msgEl = document.getElementById("message");
    if (data.result === "low") msgEl.textContent = "Too Low! 🔽";
    else if (data.result === "high") msgEl.textContent = "Too High! 🔼";
    else if (data.result === "correct") msgEl.textContent =
      `🎉 Correct! Number was ${data.number}. New game started!`;

    } catch (err) {
        console.error(err);
        document.getElementById("message").textContent = "Error connecting to server!";
    }
}
