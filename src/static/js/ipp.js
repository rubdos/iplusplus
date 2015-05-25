function searchCustomer(query, process) {
  $.ajax({
    url: "/customers/lookup/json/" + query
  })
  .done(function(data){
    process(data);
  });
}

function newInvoiceCustomerUpdated(customer) {
  // Get the newly selected customer
  $.ajax({
    url: "/customers/get/json/" + customer.id
  }).done(function(data){
    $("#selected-customer").show();
    $("#customer-first-line").text(customer.name + (data.vat_number != "" ? " BTW " + data.vat_number : ""));
    $("#customer-second-line").text(data.street_and_number);
    $("#customer-third-line").text(data.postal_code + " " + data.city);
    $("#customer-fourth-line").text(data.country);
    $("#continueLink").attr("href", "/sales_invoices/new/" + customer.id);
  });
  return customer;
}
